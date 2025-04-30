#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}TreeNode;//The definition of BSTreeNode

typedef struct QueNode {
    TreeNode *node;
    struct QueNode *next;
}QueNode;
typedef struct {
    QueNode *front;
    QueNode *rear;
}Queue;

TreeNode *CreateNode(int data) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

TreeNode* InsertIntoBSTree(TreeNode *root, int data) {
    if (root==NULL) {
        return CreateNode(data);
    }
    if (data<root->data) {
        root->left = InsertIntoBSTree(root->left, data);
    }else if (data>root->data) {
        root->right = InsertIntoBSTree(root->right, data);
    }
    return root;
}
void freeTree(TreeNode *node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}

void previousTraversal(TreeNode *root) {
    if (root==NULL) {
        return;
    }
    printf("->%d", root->data);
    previousTraversal(root->left);
    previousTraversal(root->right);
}
void middleTraversal(TreeNode *root) {
    if (root==NULL) {
        return;
    }
    middleTraversal(root->left);
    printf("->%d", root->data);
    middleTraversal(root->right);
}
void lastTraversal(TreeNode *root) {
    if (root==NULL) {
        return;
    }
    lastTraversal(root->left);
    lastTraversal(root->right);
    printf("->%d", root->data);
}
void initializeQue(Queue **que) {
    *que = (Queue *)malloc(sizeof(Queue));
    (*que)->front = (*que)->rear = NULL;
}
void insertIntoQueue(Queue *que, TreeNode *node) {
    QueNode *newNode = (QueNode *)malloc(sizeof(QueNode));
    newNode->node = node;
    newNode->next = NULL;
    if (que->rear) {
        que->rear->next = newNode;
    }
    que->rear = newNode;
    if (que->front==NULL) {
        que->front=newNode;
    }
}

bool isEmptyQueue(Queue *que) {
    if (que->front==NULL) {
        return true;
    }
    return false;
}
TreeNode* outFromQueue(Queue *que) {
    if (isEmptyQueue(que)) {
        return NULL;
    }
    TreeNode *node = que->front->node;
    que->front = que->front->next;
    if (que->front==NULL) {
        que->rear=NULL;
    }
    return node;
}
void levelTraversal(TreeNode *root) {
    if (root==NULL) {
        return;
    }
    Queue *que;
    initializeQue(&que);
    insertIntoQueue(que,root);
    while (!isEmptyQueue(que)) {
        TreeNode *current_node=outFromQueue(que);
        printf("->%d", current_node->data);
        if (current_node->left) {
           insertIntoQueue(que,current_node->left);
        }
        if (current_node->right) {
            insertIntoQueue(que,current_node->right);
        }
    }
    free(que);
}
TreeNode* initializeData(TreeNode *root) {
    root=InsertIntoBSTree(root,10);
    root=InsertIntoBSTree(root,20);
    root=InsertIntoBSTree(root,30);
    root=InsertIntoBSTree(root,5);
    root=InsertIntoBSTree(root,15);
    root=InsertIntoBSTree(root,25);
    return root;
}
void printTree(TreeNode *root) {
    printf("先序遍历:");
    previousTraversal(root);
    printf("\n");
    printf("中序遍历:");
    middleTraversal(root);
    printf("\n");
    printf("后序遍历:");
    lastTraversal(root);
    printf("\n");
    printf("层序遍历:");
    levelTraversal(root);
}
int main(){
    TreeNode *root=NULL;
    root=initializeData(root);
    printTree(root);
    freeTree(root);
    return 0;
}