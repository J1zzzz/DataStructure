//
// Created by 86152 on 2025/5/19.
//
#include <stdio.h>
#include <stdlib.h>

// 定义树节点结构
typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

// 创建新节点
AVLNode* createNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// 获取节点高度
int getHeight(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

// 获取平衡因子
int getBalance(AVLNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 获取最大值
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 右旋操作
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // 执行旋转
    x->right = y;
    y->left = T2;

    // 更新高度
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    // 返回新的根节点
    return x;
}

// 左旋操作
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // 执行旋转
    y->left = x;
    x->right = T2;

    // 更新高度
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    // 返回新的根节点
    return y;
}

// 插入节点
AVLNode* insert(AVLNode* node, int key) {
    // 1. 执行标准的BST插入
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // 不允许重复键
        return node;

    // 2. 更新当前节点的高度
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));

    // 3. 获取当前节点的平衡因子，检查是否失衡
    int balance = getBalance(node);

    // 如果失衡，需要进行四种情况的调整

    // 左左情况
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // 右右情况
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // 左右情况
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // 右左情况
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // 返回不变的节点指针
    return node;
}

// 查找最小节点
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    // 循环查找最左节点
    while (current->left != NULL)
        current = current->left;
    return current;
}

// 删除节点
AVLNode* deleteNode(AVLNode* root, int key) {
    // 1. 执行标准的BST删除
    if (root == NULL)
        return root;

    // 如果要删除的键小于根节点的键，则在左子树中删除
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // 如果要删除的键大于根节点的键，则在右子树中删除
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // 如果键相同，则这是要删除的节点
    else {
        // 节点只有一个子节点或没有子节点
        if ((root->left == NULL) || (root->right == NULL)) {
            AVLNode* temp = root->left ? root->left : root->right;

            // 没有子节点的情况
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else // 有一个子节点的情况
                *root = *temp; // 复制子节点的内容到当前节点

            free(temp);
        } else {
            // 节点有两个子节点：获取右子树的最小节点（中序后继）
            AVLNode* temp = minValueNode(root->right);

            // 复制中序后继的内容到当前节点
            root->key = temp->key;

            // 删除中序后继
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // 如果树只有一个节点，直接返回
    if (root == NULL)
        return root;

    // 2. 更新当前节点的高度
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    // 3. 获取当前节点的平衡因子，检查是否失衡
    int balance = getBalance(root);

    // 如果失衡，需要进行四种情况的调整

    // 左左情况
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // 左右情况
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // 右右情况
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // 右左情况
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 中序遍历
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->key);
        inorderTraversal(root->right);
    }
}

// 前序遍历
void preorderTraversal(AVLNode* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// 释放树
void freeTree(AVLNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    AVLNode* root = NULL;

    // 插入节点
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    /* 插入后的AVL树结构
              30
             /  \
           20   40
          /  \    \
        10   25    50
    */

    printf("中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");

    printf("前序遍历结果: ");
    preorderTraversal(root);
    printf("\n");

    // 删除节点
    root = deleteNode(root, 40);

    /* 删除后的AVL树结构
              25
             /  \
           20   30
          /       \
        10        50
    */

    printf("删除40后的中序遍历结果: ");
    inorderTraversal(root);
    printf("\n");

    printf("删除40后的前序遍历结果: ");
    preorderTraversal(root);
    printf("\n");

    // 释放树内存
    freeTree(root);

    return 0;
}