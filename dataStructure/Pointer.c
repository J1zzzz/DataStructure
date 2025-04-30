#include <stdio.h>
#include <stdlib.h>
//
// Created by 86152 on 2025/4/29.
//
void changeValue(int **p) {
    *p=(int *)malloc(sizeof(int *));
    **p=111;
    // **p=123;
}
void changeValue2(int *p) {
    p=(int *)malloc(sizeof(int *));
    // **p=123;
}
void changePointer(int *p) {
    *p=111;
}
int main() {
    int a_i=1;
    int *a=NULL;
    printf("%p\n",&a_i);
    printf("%p\n",&a);
    // printf("%p\n",a);
int *b=&a_i;
    changePointer(b);
    changeValue2(&a_i);
    printf("%d\n",*b);
    changeValue(&a);
    printf("%d\n",*a);
}
// 在 C 语言中，函数参数是通过值传递的。这意味着当我们将一个指针传递给函数时，函数内部获得的是该指针的副本，而不是指针本身。
// 如果我们希望在函数内部修改指针本身的值（例如让它指向一个新的地址），就需要传递指针的地址，即使用二层指针。