//
// Created by 86152 on 2025/5/26.
//
#include <stdio.h>
#include <stdlib.h>

// 计数排序函数（假设数据范围已知：0 <= arr[i] <= maxValue）
void countingSort(int arr[], int n, int maxValue) {
    int* count = (int*)malloc((maxValue + 1) * sizeof(int)); // 计数数组
    int* output = (int*)malloc(n * sizeof(int)); // 输出数组

    // 初始化计数数组为0
    for (int i = 0; i <= maxValue; i++) {
        count[i] = 0;
    }

    // 统计每个元素的出现次数
    for (int i = 0; i < n; i++) {
        count[arr[i]]++;
    }

    // 计算累积计数（确定元素在输出数组中的位置）
    for (int i = 1; i <= maxValue; i++) {
        count[i] += count[i - 1];
    }

    // 构建输出数组（从后往前遍历保证稳定性）
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i]; // 减去1得到0-based索引
        count[arr[i]]--; // 处理下一个相同元素时位置减1
    }

    // 将排序结果复制回原数组
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
    }

    // 释放内存
    free(count);
    free(output);
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// 主函数
int main() {
    int arr[] = {4, 2, 2, 8, 3, 3, 1};
    int n = sizeof(arr) / sizeof(arr[0]);
    int maxValue = 8; // 数组中的最大值（需根据实际数据调整）

    printf("排序前的数组: ");
    printArray(arr, n);

    countingSort(arr, n, maxValue);

    printf("排序后的数组: ");
    printArray(arr, n);

    return 0;
}