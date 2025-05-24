//
// Created by 86152 on 2025/5/24.
//
#include <stdio.h>

// 希尔排序函数（数组下标从1开始，0号位置作为哨兵位）
void shellSort(int arr[], int n) {
    // 初始增量为数组长度的一半，逐步缩小增量
    for (int gap = n/2; gap > 0; gap /= 2) {
        // 对每个增量进行插入排序
        for (int i = gap + 1; i <= n; i++) {  // 从gap+1开始，因为数组下标从1开始
            arr[0] = arr[i];  // 将当前元素存入哨兵位
            int j;
            // 对相隔gap位置的元素进行比较和交换
            for (j = i; j > gap && arr[j - gap] > arr[0]; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = arr[0];  // 将哨兵位的值（原arr[i]）插入正确位置
        }
    }
}

// 打印数组函数
void printArray(int arr[], int n) {
    for (int i = 1; i <= n; i++) {  // 注意下标从1开始
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 主函数
int main() {
    int arr[] = {0, 12, 34, 54, 2, 3};  // 注意：0号位置用于哨兵，实际数据从下标1开始
    int n = sizeof(arr)/sizeof(arr[0]) - 1;  // 有效元素个数（不包括下标0）

    printf("排序前的数组：\n");
    printArray(arr, n);

    shellSort(arr, n);

    printf("排序后的数组：\n");
    printArray(arr, n);

    return 0;
}
