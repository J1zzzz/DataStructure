#include <stdio.h>
#include <stdlib.h>

// 定义二叉树结点结构
typedef struct ThreadNode {
    char data; // 结点数据
    struct ThreadNode *lchild, *rchild; // 左右孩子指针
    int ltag, rtag; // 左右线索标志
} ThreadNode, *ThreadTree;

// 创建二叉树（递归方式）
ThreadTree CreateTree() {
    char ch;
    scanf(" %c", &ch); // 输入结点数据，空格分隔
    if (ch == '#') {
        return NULL; // 如果输入为'#'，表示空结点
    }
    ThreadTree node = (ThreadTree)malloc(sizeof(ThreadNode));
    node->data = ch;
    node->ltag = node->rtag = 0; // 初始化线索标志为0
    node->lchild = CreateTree(); // 递归创建左子树
    node->rchild = CreateTree(); // 递归创建右子树
    return node;
}

// 先序线索化函数
void PreOrderThreading(ThreadTree T, ThreadTree *pre) {
    if (T != NULL) {
        if (T->lchild == NULL) { // 左孩子为空，建立前驱线索
            T->lchild = *pre;
            T->ltag = 1;
        }
        if (*pre != NULL && (*pre)->rchild == NULL) { // 前驱的右孩子为空，建立后继线索
            (*pre)->rchild = T;
            (*pre)->rtag = 1;
        }
        *pre = T; // 当前结点成为下一个结点的前驱
        if (T->ltag == 0) { // 左孩子存在，递归线索化左子树
            PreOrderThreading(T->lchild, pre);
        }
        if (T->rtag == 0) { // 右孩子存在，递归线索化右子树
            PreOrderThreading(T->rchild, pre);
        }
    }
}

// 建立先序线索二叉树
void CreatePreOrderThread(ThreadTree T) {
    ThreadTree pre = NULL; // 初始化前驱指针
    PreOrderThreading(T, &pre); // 调用线索化函数
}

// 先序线索二叉树遍历函数
void PreOrderTraverse(ThreadTree T) {
    ThreadTree pre = NULL; // 初始化前驱指针
    while (T != NULL) {
        while (T->ltag == 0) { // 沿左子树向下
            printf("%c ", T->data); // 访问结点
            pre = T; // 更新前驱
            T = T->lchild;
        }
        printf("%c ", T->data); // 访问结点
        while (T->rtag == 1 && T->rchild != NULL) { // 沿后继线索向右
            T = T->rchild;
            printf("%c ", T->data); // 访问结点
        }
        T = T->rchild; // 转向右子树
    }
}

// 主函数
int main() {
    ThreadTree T = NULL; // 初始化空树
    printf("请输入二叉树的结点数据（#表示空结点）：\n");
    T = CreateTree(); // 创建二叉树

    // 建立先序线索二叉树
    CreatePreOrderThread(T);

    // 遍历先序线索二叉树
    printf("先序线索二叉树遍历结果：\n");
    PreOrderTraverse(T);
    printf("\n");

    return 0;
}