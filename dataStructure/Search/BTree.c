//
// Created by 86152 on 2025/5/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// B树节点结构定义
#define MIN_DEGREE 3

typedef struct BTreeNode {
    int *keys;           // 键数组
    int t;               // 最小度数 (定义节点中键的数量范围)
    struct BTreeNode **children; // 子节点指针数组
    int n;               // 当前键的数量
    bool leaf;           // 是否为叶子节点
} BTreeNode;

// 创建新的B树节点
BTreeNode* createNode(int t, bool leaf) {
    BTreeNode* node = (BTreeNode*)malloc(sizeof(BTreeNode));
    node->t = t;
    node->leaf = leaf;
    node->keys = (int*)malloc((2*t-1) * sizeof(int));
    node->children = (BTreeNode**)malloc(2*t * sizeof(BTreeNode*));
    node->n = 0;
    return node;
}

// 遍历B树
void traverse(BTreeNode* root) {
    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->children[i]);
        printf(" %d", root->keys[i]);
    }
    if (!root->leaf)
        traverse(root->children[i]);
}

// 在满节点中分裂子节点
void splitChild(BTreeNode* parent, int i, BTreeNode* child) {
    int t = parent->t;
    BTreeNode* newNode = createNode(t, child->leaf);
    newNode->n = t - 1;

    for (int j = 0; j < t-1; j++)
        newNode->keys[j] = child->keys[j+t];

    if (!child->leaf) {
        for (int j = 0; j < t; j++)
            newNode->children[j] = child->children[j+t];
    }

    child->n = t - 1;

    for (int j = parent->n; j >= i+1; j--)
        parent->children[j+1] = parent->children[j];

    parent->children[i+1] = newNode;

    for (int j = parent->n-1; j >= i; j--)
        parent->keys[j+1] = parent->keys[j];

    parent->keys[i] = child->keys[t-1];
    parent->n = parent->n + 1;
}

// 插入非满节点
void insertNonFull(BTreeNode* node, int key) {
    int i = node->n - 1;

    if (node->leaf) {
        while (i >= 0 && node->keys[i] > key) {
            node->keys[i+1] = node->keys[i];
            i--;
        }
        node->keys[i+1] = key;
        node->n = node->n + 1;
    } else {
        while (i >= 0 && node->keys[i] > key)
            i--;

        if (node->children[i+1]->n == 2*node->t-1) {
            splitChild(node, i+1, node->children[i+1]);
            if (node->keys[i+1] < key)
                i++;
        }
        insertNonFull(node->children[i+1], key);
    }
}

// 插入新键
BTreeNode* insert(BTreeNode* root, int key) {
    int t = root->t;
    if (root->n == 2*t-1) {
        BTreeNode* newRoot = createNode(t, false);
        newRoot->children[0] = root;
        splitChild(newRoot, 0, root);
        int i = 0;
        if (newRoot->keys[0] < key)
            i++;
        insertNonFull(newRoot->children[i], key);
        return newRoot;
    } else {
        insertNonFull(root, key);
        return root;
    }
}

// 查找键
BTreeNode* search(BTreeNode* root, int key) {
    int i = 0;
    while (i < root->n && key > root->keys[i])
        i++;

    if (root->keys[i] == key)
        return root;

    if (root->leaf)
        return NULL;

    return search(root->children[i], key);
}

// 查找前驱
int findPredecessor(BTreeNode* node, int idx) {
    BTreeNode* current = node->children[idx];
    while (!current->leaf)
        current = current->children[current->n];
    return current->keys[current->n-1];
}

// 查找后继
int findSuccessor(BTreeNode* node, int idx) {
    BTreeNode* current = node->children[idx+1];
    while (!current->leaf)
        current = current->children[0];
    return current->keys[0];
}

// 合并子节点
void merge(BTreeNode* node, int idx) {
    BTreeNode* child = node->children[idx];
    BTreeNode* sibling = node->children[idx+1];

    child->keys[child->t-1] = node->keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i+child->t] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->children[i+child->t] = sibling->children[i];
    }

    for (int i = idx+1; i < node->n; i++)
        node->keys[i-1] = node->keys[i];

    for (int i = idx+2; i <= node->n; i++)
        node->children[i-1] = node->children[i];

    child->n += sibling->n + 1;
    node->n--;

    free(sibling);
}

// 从B树中删除键
void deleteKey(BTreeNode* root, int key) {
    int idx = 0;
    while (idx < root->n && key > root->keys[idx])
        idx++;

    if (idx < root->n && root->keys[idx] == key) {
        if (root->leaf) {
            for (int i = idx; i < root->n-1; i++)
                root->keys[i] = root->keys[i+1];
            root->n--;
        } else {
            BTreeNode* child = root->children[idx];
            BTreeNode* sibling = root->children[idx+1];

            if (child->n >= root->t) {
                int pred = findPredecessor(root, idx);
                root->keys[idx] = pred;
                deleteKey(child, pred);
            } else if (sibling->n >= root->t) {
                int succ = findSuccessor(root, idx);
                root->keys[idx] = succ;
                deleteKey(sibling, succ);
            } else {
                merge(root, idx);
                deleteKey(child, key);
            }
        }
    } else {
        if (root->leaf) {
            printf("Key %d not found in the B-tree\n", key);
            return;
        }

        int childIdx = idx;
        BTreeNode* child = root->children[childIdx];

        if (child->n < root->t) {
            if (childIdx > 0 && root->children[childIdx-1]->n >= root->t) {
                // 从左兄弟借
                BTreeNode* leftSibling = root->children[childIdx-1];

                for (int i = child->n; i > 0; i--)
                    child->keys[i] = child->keys[i-1];

                if (!child->leaf) {
                    for (int i = child->n+1; i > 0; i--)
                        child->children[i] = child->children[i-1];
                }

                child->keys[0] = root->keys[childIdx-1];

                if (!child->leaf)
                    child->children[0] = leftSibling->children[leftSibling->n];

                root->keys[childIdx-1] = leftSibling->keys[leftSibling->n-1];

                child->n += 1;
                leftSibling->n -= 1;
            } else if (childIdx < root->n && root->children[childIdx+1]->n >= root->t) {
                // 从右兄弟借
                BTreeNode* rightSibling = root->children[childIdx+1];

                child->keys[child->n] = root->keys[childIdx];

                if (!child->leaf)
                    child->children[child->n+1] = rightSibling->children[0];

                root->keys[childIdx] = rightSibling->keys[0];

                for (int i = 0; i < rightSibling->n-1; i++)
                    rightSibling->keys[i] = rightSibling->keys[i+1];

                if (!rightSibling->leaf) {
                    for (int i = 0; i < rightSibling->n; i++)
                        rightSibling->children[i] = rightSibling->children[i+1];
                }

                child->n += 1;
                rightSibling->n -= 1;
            } else {
                // 合并
                if (childIdx > 0) {
                    merge(root, childIdx-1);
                    child = root->children[childIdx-1];
                } else {
                    merge(root, childIdx);
                }
            }
        }
        deleteKey(child, key);
    }
}

// 主函数测试B树操作
int main() {
    BTreeNode* root = createNode(MIN_DEGREE, true);

    // 插入测试
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 12);
    root = insert(root, 30);
    root = insert(root, 7);
    root = insert(root, 17);

    printf("B树遍历结果:\n");
    traverse(root);
    printf("\n");

    // 搜索测试
    BTreeNode* result = search(root, 6);
    printf("搜索键6: %s\n", result ? "找到" : "未找到");

    result = search(root, 15);
    printf("搜索键15: %s\n", result ? "找到" : "未找到");

    // 删除测试
    printf("删除键6\n");
    deleteKey(root, 6);

    printf("删除后的B树遍历结果:\n");
    traverse(root);
    printf("\n");

    return 0;
}