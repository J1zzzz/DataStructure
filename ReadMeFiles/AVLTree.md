# C语言平衡二叉树(AVL树)实现

这个项目实现了平衡二叉树(AVL树)的基本功能，包括节点插入、删除、查找和遍历操作。AVL树是一种自平衡二叉搜索树，通过维护树的平衡来保证插入、删除和查找操作的时间复杂度为O(log n)。

## 特性

- 自平衡机制确保树的高度始终保持平衡
- 支持插入、删除、查找等基本操作
- 提供中序和前序遍历方式
- 完整的内存管理，避免内存泄漏

## 数据结构

```c
typedef struct AVLNode {
    int key;           // 节点键值
    int height;        // 节点高度，用于计算平衡因子
    struct AVLNode *left;   // 左子节点
    struct AVLNode *right;  // 右子节点
} AVLNode;
```

## 核心函数

- `createNode(int key)`: 创建新节点
- `insert(AVLNode* node, int key)`: 插入节点并自动平衡树
- `deleteNode(AVLNode* root, int key)`: 删除节点并重新平衡树
- `rightRotate(AVLNode* y)` 和 `leftRotate(AVLNode* x)`: 树旋转操作
- `getHeight(AVLNode* node)`: 获取节点高度
- `getBalance(AVLNode* node)`: 计算节点平衡因子
- `inorderTraversal(AVLNode* root)` 和 `preorderTraversal(AVLNode* root)`: 树遍历

## 平衡维护核心机制

AVL树通过平衡因子（左子树高度减去右子树高度）来维护平衡，当平衡因子的绝对值超过1时，需要通过旋转操作来恢复平衡。旋转操作是AVL树的核心机制，主要分为四种情况：

### 四种失衡类型及旋转操作

#### 1. LL型失衡（左左情况）
**失衡原因**：在节点的左子树的左子树插入新节点，导致平衡因子 > 1。
**调整方式**：进行一次右旋操作。

```
    z                               y
   / \                            /   \ 
  y   T4  右旋(z)               x      z
 / \      ------->            /  \    /  \ 
x   T3                       T1  T2  T3  T4
/ \
T1 T2
```

**代码实现**：
```c
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

    return x;
}
```

#### 2. RR型失衡（右右情况）
**失衡原因**：在节点的右子树的右子树插入新节点，导致平衡因子 < -1。
**调整方式**：进行一次左旋操作。

```
    z                            y
   / \                         /   \ 
  T1  y    左旋(z)            z      x
     / \   ------->         / \    / \ 
    T2  x                  T1 T2  T3 T4
       / \
      T3 T4
```

**代码实现**：
```c
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

    return y;
}
```

#### 3. LR型失衡（左右情况）
**失衡原因**：在节点的左子树的右子树插入新节点。
**调整方式**：先对左子树进行左旋，再对根节点进行右旋。

```
     z                z                   x
    / \              / \                /   \ 
   y   T4  左旋(y)   x   T4  右旋(z)    y     z
  / \     ------->  / \     ------->  / \   / \ 
T1   x             y   T3            T1 T2 T3 T4
    / \           / \
   T2 T3         T1 T2
```

**代码实现**：
```c
// 在insert函数中处理LR情况
if (balance > 1 && key > node->left->key) {
    node->left = leftRotate(node->left);
    return rightRotate(node);
}
```

#### 4. RL型失衡（右左情况）
**失衡原因**：在节点的右子树的左子树插入新节点。
**调整方式**：先对右子树进行右旋，再对根节点进行左旋。

```
    z                z                    x
   / \              / \                 /   \ 
 T1   y   右旋(y)  T1   x    左旋(z)    z     y
    / \  ------->     / \   ------->  / \   / \ 
   x   T4            T2  y           T1 T2 T3 T4
  / \                    / \
 T2 T3                  T3 T4
```

**代码实现**：
```c
// 在insert函数中处理RL情况
if (balance < -1 && key < node->right->key) {
    node->right = rightRotate(node->right);
    return leftRotate(node);
}
```

## 平衡维护流程

在插入或删除操作后，AVL树会：
1. 更新受影响节点的高度
2. 从插入/删除节点向上回溯，检查每个节点的平衡因子
3. 若发现平衡因子超过阈值（±1），则根据失衡类型执行对应的旋转操作

## 使用示例

以下代码展示了如何使用这个AVL树实现：

```c
#include <stdio.h>
#include "avl_tree.h"  // 假设代码已放入头文件

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
```

## 编译和运行

将代码保存为`avl_tree.c`，使用以下命令编译：

```bash
gcc avl_tree.c -o avl_tree
./avl_tree
```



