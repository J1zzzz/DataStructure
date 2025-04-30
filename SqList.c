//
// Created by Jzzzz on 2025/4/30.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
typedef int ElementType;
typedef struct Node{
    int data;
    struct Node *next;
}Node,*SqList;//The definition of SqList
//尾插法建立链表
void InsertTail(SqList *L,ElementType data) {
    Node *q;
    Node *p = *L;
    while(p->next!=NULL) {
        p=p->next;
    }
    q=(Node*)malloc(sizeof(Node));
    q->data=data;
    q->next=p->next;
    p->next=q;
}
//头插法建立链表
void InsertHead(SqList *L,ElementType data) {
    Node *q;
    q=(Node*)malloc(sizeof(Node));
    q->data=data;
    q->next=(*L)->next;
    (*L)->next=q;
}
//创建链表，带有头节点的链表
void Initialize(SqList *L){
    *L=(Node*)malloc(sizeof(Node));
    if (*L==NULL) {
        printf("Memory allocation error");
    }
    (*L)->next=NULL;
    InsertHead(L,2);
    InsertTail(L,2);
}
//判断链表是否为空
bool IsEmpty(SqList *L) {
   return (*L)->next==NULL;
}
//遍历链表
void Traverse(SqList L) {
    if (IsEmpty(&L)) {
        printf("链表为空!!");
        return;
    }
    Node *p=L->next;
    while(p!=NULL) {
        printf("%d ",p->data);
        p=p->next;
    }
}
//将某位置的数据读出，头节点为零号元素
void OutFromSqlistByPosition(SqList *L,int position) {
    if (IsEmpty(L)) {
        printf("链表为空!!!");
        return;
    }
    Node *p=*L;
    int i=0;
    while(p->next!=NULL) {
        i++;
        if(i==position) {
            break;
        }
        p=p->next;
    }
    printf("%d",p->next->data);
    Node *q=p->next;
    p->next=q->next;
    free(q);
}
//删除链表中所有匹配正确的节点
int OutFromSqlistByValue(SqList *L,ElementType data) {
    if (IsEmpty(L)) {
        return 0;
    }
    Node *p=*L;
    int times=0;
    while(p->next!=NULL) {
        if (p->next->data==data) {
            times++;
            Node *q=p->next;
            p->next=q->next;
            free(q);
        }else {
            p=p->next;
        }
        if (p==NULL) {
            break;
        }
    }
    if (p==NULL&&times==0) {
        printf("Can't find ‘%d’",data);
    }
    return times;
}
//链表的删除操作
void DestroyList(SqList *L) {
    Node *p=*L;
    while(p!=NULL) {
        Node *p2=p->next;
        free(p);
        p=p2;
    }
}
//测试链表的输出
void TestSqList(SqList *L) {
    printf("按位置删除节点: ");
    OutFromSqlistByPosition(L,1);
    printf("\n");
    printf("按值删除节点: ");
    int times=OutFromSqlistByValue(L,1);
    printf("链表中此值的个数是%d",times);
    printf("\n");
    printf("遍历: ");
    Traverse(*L);
}
int main()
{
    SqList L=NULL;
    Initialize(&L);
    TestSqList(&L);
    DestroyList(&L);
}


