//
// Created by 86152 on 2025/5/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDER 4  // B+树的阶数，可根据需要调整

// B+树节点结构
typedef struct BPlusTreeNode {
    bool is_leaf;          // 是否为叶子节点
    int num_keys;          // 当前键的数量
    int *keys;             // 键数组
    struct BPlusTreeNode **children;  // 子节点指针数组
    struct BPlusTreeNode *next;       // 叶子节点的下一个指针（用于链表）
} BPlusTreeNode;

// 创建新节点
BPlusTreeNode* createNode(bool is_leaf) {
    BPlusTreeNode* node = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->keys = (int*)malloc((ORDER - 1) * sizeof(int));
    node->children = (BPlusTreeNode**)malloc(ORDER * sizeof(BPlusTreeNode*));
    node->next = NULL;
    return node;
}

// 查找键
bool search(BPlusTreeNode* root, int key) {
    if (root == NULL) return false;

    int i = 0;
    // 找到第一个大于等于key的位置
    while (i < root->num_keys && key > root->keys[i])
        i++;

    // 如果在当前节点找到key
    if (i < root->num_keys && key == root->keys[i])
        return root->is_leaf;  // 只在叶子节点存储数据

    // 递归查找子节点
    if (root->is_leaf)
        return false;
    else
        return search(root->children[i], key);
}

// 插入键（内部函数）
void insertNonFull(BPlusTreeNode* node, int key);

// 分裂子节点
void splitChild(BPlusTreeNode* parent, int index, BPlusTreeNode* child);

// 插入键
BPlusTreeNode* insert(BPlusTreeNode* root, int key) {
    if (root == NULL) {
        root = createNode(true);
        root->keys[0] = key;
        root->num_keys = 1;
        return root;
    }

    // 如果根节点已满，分裂根节点
    if (root->num_keys == ORDER - 1) {
        BPlusTreeNode* new_root = createNode(false);
        new_root->children[0] = root;
        splitChild(new_root, 0, root);

        // 决定新键应该插入到哪个子节点
        int i = 0;
        if (key > new_root->keys[0])
            i++;
        insertNonFull(new_root->children[i], key);

        return new_root;
    } else {
        // 根节点未满，直接插入
        insertNonFull(root, key);
        return root;
    }
}

// 非满节点插入键
void insertNonFull(BPlusTreeNode* node, int key) {
    int i = node->num_keys - 1;

    // 如果是叶子节点，直接插入
    if (node->is_leaf) {
        // 找到插入位置
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        // 插入新键
        node->keys[i + 1] = key;
        node->num_keys++;
    } else {
        // 如果不是叶子节点，找到合适的子节点
        while (i >= 0 && key < node->keys[i])
            i--;
        i++;

        // 如果子节点已满，分裂
        if (node->children[i]->num_keys == ORDER - 1) {
            splitChild(node, i, node->children[i]);

            // 决定新键应该插入到分裂后的哪个子节点
            if (key > node->keys[i])
                i++;
        }

        // 递归插入到子节点
        insertNonFull(node->children[i], key);
    }
}

// 分裂子节点
void splitChild(BPlusTreeNode* parent, int index, BPlusTreeNode* child) {
    // 创建新节点
    BPlusTreeNode* new_node = createNode(child->is_leaf);
    new_node->num_keys = ORDER / 2 - 1;

    // 复制后一半的键到新节点
    for (int i = 0; i < new_node->num_keys; i++)
        new_node->keys[i] = child->keys[i + ORDER / 2];

    // 如果不是叶子节点，复制后一半的子节点
    if (!child->is_leaf) {
        for (int i = 0; i <= new_node->num_keys; i++)
            new_node->children[i] = child->children[i + ORDER / 2];
    }

    // 更新原节点的键数量
    child->num_keys = ORDER / 2 - 1;

    // 在父节点中插入新节点
    for (int i = parent->num_keys; i > index; i--)
        parent->children[i + 1] = parent->children[i];

    parent->children[index + 1] = new_node;

    // 将中间键提升到父节点
    for (int i = parent->num_keys - 1; i >= index; i--)
        parent->keys[i + 1] = parent->keys[i];

    parent->keys[index] = child->keys[ORDER / 2 - 1];
    parent->num_keys++;

    // 如果是叶子节点，设置链表指针
    if (child->is_leaf) {
        new_node->next = child->next;
        child->next = new_node;
    }
}

// 遍历B+树（按顺序打印所有键）
void traverse(BPlusTreeNode* root) {
    if (root == NULL) return;

    BPlusTreeNode* current = root;
    // 找到最左边的叶子节点
    while (!current->is_leaf)
        current = current->children[0];

    // 遍历叶子节点链表
    while (current != NULL) {
        for (int i = 0; i < current->num_keys; i++)
            printf("%d ", current->keys[i]);
        current = current->next;
    }
    printf("\n");
}

// 释放B+树内存
void freeTree(BPlusTreeNode* root) {
    if (root == NULL) return;

    // 如果不是叶子节点，递归释放子节点
    if (!root->is_leaf) {
        for (int i = 0; i <= root->num_keys; i++)
            freeTree(root->children[i]);
    }

    // 释放当前节点
    free(root->keys);
    free(root->children);
    free(root);
}

// 示例用法
int main() {
    BPlusTreeNode* root = NULL;

    // 插入示例数据
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 12);
    root = insert(root, 30);
    root = insert(root, 7);
    root = insert(root, 17);

    // 遍历B+树
    printf("B+树按顺序遍历结果：\n");
    traverse(root);

    // 查找示例
    printf("查找键 6: %s\n", search(root, 6) ? "找到" : "未找到");
    printf("查找键 15: %s\n", search(root, 15) ? "找到" : "未找到");

    // 释放内存
    freeTree(root);

    return 0;
}