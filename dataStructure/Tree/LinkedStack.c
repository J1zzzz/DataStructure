//
// Created by 86152 on 2025/5/1.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int ElementType;
typedef struct node {
    ElementType data;
    struct node *next;
} StackNode;//The definition of StackNode
typedef struct stack {
    StackNode *top;
} Stack;//the definition of Stack
//初始化栈
void InitStack(Stack *s) {
    s ->top= NULL;
}
//判断栈是否为空
bool IsEmptyStack(Stack *s) {
    if (s->top == NULL) {
        printf("Stack is empty\n");
        return true;
    }
    return false;
}
//删除栈并释放栈的内存
void DestroyStack(Stack *s) {
    while (s->top != NULL) {
        StackNode *p= s->top;
        s->top = s->top->next;
        free(p);
    }
}
//进栈操作
void PushStack(Stack *s,ElementType data_element) {
    StackNode *p=(StackNode *)malloc(sizeof(StackNode));
    p->data=data_element;
    p->next=s->top;
    s->top=p;
}
//出栈操作
void PopStack(Stack *s) {
    if (IsEmptyStack(s)) {
        printf("Stack is empty\n");
        return;
    }
    StackNode *p=s->top;
    printf("Element in the stack on the top: %d\n",p->data);
    s->top=p->next;
    free(p);
}
//将栈内元素按栈顶输出
void DisplayStack(Stack *s) {
    if (IsEmptyStack(s)) {
        printf("Stack is empty\n");
        return;
    }
    StackNode *p=s->top;
    while (p != NULL) {
        printf("%d ",p->data);
        p=p->next;
    }
}

int main(){
    Stack s;
    InitStack(&s);
    PushStack(&s,1);
    PushStack(&s,2);
    PopStack(&s);
    DisplayStack(&s);
    DestroyStack(&s);
}
