//
// Created by 86152 on 2025/5/21.
//
#include <stdio.h>
#include <stdlib.h>

// 定义颜色枚举
typedef enum { RED, BLACK } Color;

// 红黑树节点结构
typedef struct RBNode {
    int key;
    Color color;
    struct RBNode *left, *right, *parent;
} RBNode;

// 红黑树结构
typedef struct RBTree {
    RBNode *root;
    RBNode *NIL; // 哨兵节点
} RBTree;

// 创建新节点
RBNode* newNode(RBTree *tree, int key, Color color) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->key = key;
    node->color = color;
    node->left = tree->NIL;
    node->right = tree->NIL;
    node->parent = tree->NIL;
    return node;
}

// 创建红黑树
RBTree* createTree() {
    RBTree* tree = (RBTree*)malloc(sizeof(RBTree));
    tree->NIL = (RBNode*)malloc(sizeof(RBNode));
    tree->NIL->color = BLACK;
    tree->NIL->left = NULL;
    tree->NIL->right = NULL;
    tree->root = tree->NIL;
    return tree;
}

// 左旋操作
void leftRotate(RBTree *tree, RBNode *x) {
    RBNode *y = x->right;
    x->right = y->left;

    if (y->left != tree->NIL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == tree->NIL)
        tree->root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// 右旋操作
void rightRotate(RBTree *tree, RBNode *y) {
    RBNode *x = y->left;
    y->left = x->right;

    if (x->right != tree->NIL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == tree->NIL)
        tree->root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

// 插入修复
void insertFixup(RBTree *tree, RBNode *z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            RBNode *y = z->parent->parent->right;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(tree, z->parent->parent);
            }
        } else {
            RBNode *y = z->parent->parent->left;

            if (y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(tree, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(tree, z->parent->parent);
            }
        }
    }
    tree->root->color = BLACK;
}

// 插入节点
void insert(RBTree *tree, int key) {
    RBNode *z = newNode(tree, key, RED);
    RBNode *y = tree->NIL;
    RBNode *x = tree->root;

    while (x != tree->NIL) {
        y = x;
        if (z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == tree->NIL)
        tree->root = z;
    else if (z->key < y->key)
        y->left = z;
    else
        y->right = z;

    insertFixup(tree, z);
}

// 替换子树
void transplant(RBTree *tree, RBNode *u, RBNode *v) {
    if (u->parent == tree->NIL)
        tree->root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    v->parent = u->parent;
}

// 删除修复
void deleteFixup(RBTree *tree, RBNode *x) {
    while (x != tree->root && x->color == BLACK) {
        if (x == x->parent->left) {
            RBNode *w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(tree, x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(tree, w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(tree, x->parent);
                x = tree->root;
            }
        } else {
            RBNode *w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(tree, x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(tree, w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(tree, x->parent);
                x = tree->root;
            }
        }
    }
    x->color = BLACK;
}

// 删除节点
void deleteNode(RBTree *tree, int key) {
    RBNode *z = tree->root;
    while (z != tree->NIL && z->key != key) {
        if (key < z->key)
            z = z->left;
        else
            z = z->right;
    }

    if (z == tree->NIL) return;

    RBNode *y = z;
    RBNode *x;
    Color y_original_color = y->color;

    if (z->left == tree->NIL) {
        x = z->right;
        transplant(tree, z, z->right);
    } else if (z->right == tree->NIL) {
        x = z->left;
        transplant(tree, z, z->left);
    } else {
        y = z->right;
        while (y->left != tree->NIL)
            y = y->left;

        y_original_color = y->color;
        x = y->right;

        if (y->parent == z)
            x->parent = y;
        else {
            transplant(tree, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(tree, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_original_color == BLACK)
        deleteFixup(tree, x);

    free(z);
}

// 中序遍历
void inorder(RBTree *tree, RBNode *node) {
    if (node != tree->NIL) {
        inorder(tree, node->left);
        printf("%d ", node->key);
        inorder(tree, node->right);
    }
}

// 测试代码
int main() {
    RBTree *tree = createTree();

    // 插入测试数据
    insert(tree, 5);
    insert(tree, 3);
    insert(tree, 7);
    insert(tree, 2);
    insert(tree, 4);
    insert(tree, 6);
    insert(tree, 8);

    printf("Inorder traversal after insertion:\n");
    inorder(tree, tree->root);
    printf("\n");

    // 删除测试
    deleteNode(tree, 3);
    printf("Inorder traversal after deleting 3:\n");
    inorder(tree, tree->root);
    printf("\n");

    return 0;
}