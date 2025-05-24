//
// Created by 86152 on 2025/5/24.
//
#include <stdio.h>

// 交换两个元素
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 调整堆，使其满足最大堆性质
void heapify(int arr[], int n, int i) {
    int largest = i;    // 初始化根节点为最大值
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点比根节点大，则更新最大值索引
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点比当前最大值大，则更新最大值索引
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大值不是根节点，则交换并继续调整
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest); // 递归调整受影响的子树
    }
}

// 堆排序主函数
void heapSort(int arr[], int n) {
    // 构建最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 逐个提取元素
    for (int i = n - 1; i > 0; i--) {
        // 将当前根节点（最大值）移到末尾
        swap(&arr[0], &arr[i]);
        // 在减少的堆上重新调整堆
        heapify(arr, i, 0);
    }
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// 主函数
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("排序前的数组：\n");
    printArray(arr, n);

    heapSort(arr, n);

    printf("排序后的数组：\n");
    printArray(arr, n);

    return 0;
}
