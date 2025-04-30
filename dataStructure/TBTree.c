//
// Created by 86152 on 2025/4/30.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义结点类型
typedef int TElemType;
typedef enum { Link, Thread } PointerTag;

typedef struct BiThrNode {
    TElemType data; // 结点数据
    struct BiThrNode* lchild, * rchild; // 左右孩子指针
    PointerTag Ltag, Rtag; // 左右指针的标志
} BiThrNode, * BiThrTree;

// 全局变量，用于记录前驱结点
BiThrTree pre = NULL;

// 创建二叉树（递归方式，前序输入）
void CreateTree(BiThrTree* tree) {
    char data;
    scanf(" %c", &data); // 输入结点数据，空结点用'#'表示
    if (data == '#') {
        *tree = NULL; // 如果是'#'，则创建空结点
    } else {
        *tree = (BiThrNode*)malloc(sizeof(BiThrNode)); // 分配内存
        if (!*tree) {
            printf("申请结点空间失败\n");
            return;
        }
        (*tree)->data = data - '0'; // 将字符转换为整数
        (*tree)->Ltag = Link; // 初始化左右指针为链接
        (*tree)->Rtag = Link;
        CreateTree(&((*tree)->lchild)); // 递归创建左子树
        CreateTree(&((*tree)->rchild)); // 递归创建右子树
    }
}

// 中序线索化函数
void InThreading(BiThrTree p) {
    if (p) {
        InThreading(p->lchild); // 递归线索化左子树

        if (!p->lchild) { // 如果当前结点没有左孩子
            p->Ltag = Thread; // 将左指针改为线索
            p->lchild = pre;
        }

        if (pre && !pre->rchild) { // 如果前驱结点没有右孩子
            pre->Rtag = Thread; // 将前驱结点的右指针改为线索
            pre->rchild = p;
        }

        pre = p; // 更新前驱结点

        InThreading(p->rchild); // 递归线索化右子树
    }
}

// 中序遍历线索二叉树
void InOrderThraverse_Thr(BiThrTree p) {
    while (p) {
        while (p->Ltag == Link) { // 找到最左侧的结点
            p = p->lchild;
        }
        printf("%d ", p->data); // 输出当前结点

        while (p->Rtag == Thread && p->rchild != NULL) { // 沿着线索向后移动
            p = p->rchild;
            printf("%d ", p->data);
        }

        p = p->rchild; // 移动到右子树
    }
}

// 主函数
int main() {
    BiThrTree t;
    printf("输入前序二叉树（用'#'表示空结点）:\n");
    CreateTree(&t); // 创建二叉树
    InThreading(t); // 中序线索化
    printf("输出中序序列:\n");
    InOrderThraverse_Thr(t); // 遍历线索二叉树
    return 0;
}
/*
 线索二叉树的优势：
    1.简化遍历操作：
        在普通二叉树中，中序遍历通常需要使用递归或栈来实现，这在某些情况下可能会导致较高的空间复杂度（尤其是递归调用栈的深度）。
    线索二叉树通过引入线索，可以直接通过指针访问中序遍历的前驱和后继节点，从而避免了递归或栈的使用，简化了遍历操作。
    2.节省空间：
        在某些应用场景中，线索二叉树可以减少递归调用栈的使用，从而节省内存空间。
    3.提高遍历效率：
        虽然线索二叉树的遍历时间复杂度仍然是 O(n)，但通过线索可以直接访问下一个节点，减少了查找前驱或后继节点的时间，从而在实际运行中提高了遍历的效率。
 */
/*测试数据：
完全二叉树：
1 2 4 # # 5 # # 3 6 # # 7 # #
    1
   / \
  2   3
 / \ / \
4  5 6  7
只有左子树的二叉树:
1 2 4 # # 5 # # #
    1
   /
  2
 / \
4   5
只有右子树的二叉树:
1 # 2 # 3 # 4 # #
    1
     \
      2
       \
        3
         \
          4
包含重复值的二叉树:
1 1 2 # # 3 # # 1 4 # # 5 # #
    1
   / \
  1   1
   \   \
    2   3
       / \
      4   5
      */