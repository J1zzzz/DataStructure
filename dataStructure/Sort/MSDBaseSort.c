//
// Created by 86152 on 2025/5/26.
//
#include <stdio.h>
#include <stdlib.h>

// 获取数组中的最大值
int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

// 根据exp位进行计数排序
void countSort(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    // 统计每个位出现的次数
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // 计算累积次数
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // 构建输出数组（保持稳定性）
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // 复制回原数组
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// LSD基数排序主函数
void radixSortLSD(int arr[], int n) {
    int max = getMax(arr, n);

    // 对每一位进行计数排序（从最低位到最高位）
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 主函数
int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("排序前的数组: \n");
    printArray(arr, n);

    radixSortLSD(arr, n);

    printf("\n排序后的数组: \n");
    printArray(arr, n);

    return 0;
}