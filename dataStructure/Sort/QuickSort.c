//
// Created by 86152 on 2025/5/24.
//
#include <stdio.h>
#include <stdlib.h>

/**
 * 快速排序的分区函数 - 选择基准元素并将数组分为两部分
 * 左侧元素小于等于基准值，右侧元素大于等于基准值
 *
 * @param arr 待分区的数组
 * @param low 分区的起始索引
 * @param high 分区的结束索引
 * @return 基准元素的最终位置
 */
int partition(int *arr, int low, int high) {
    // 选择第一个元素作为基准值
    int pivot = arr[low];

    // 双指针法：从两端向中间扫描
    while (low < high) {
        // 从右向左找到第一个小于基准值的元素
        while (low < high && arr[high] >= pivot)
            high--;
        // 将该元素放到基准值的左侧
        arr[low] = arr[high];

        // 从左向右找到第一个大于基准值的元素
        while (low < high && arr[low] <= pivot)
            low++;
        // 将该元素放到基准值的右侧
        arr[high] = arr[low];
    }

    // 将基准值放到最终位置
    arr[low] = pivot;
    return low;
}

/**
 * 快速排序的递归实现
 *
 * @param arr 待排序的数组
 * @param low 排序的起始索引
 * @param high 排序的结束索引
 */
void quickSort(int arr[], int low, int high) {
    // 递归终止条件：当分区大小小于等于1时
    if (low >= high) return;

    // 分区操作，获取基准元素的位置
    int pivot = partition(arr, low, high);

    // 递归排序基准元素左侧的子数组
    quickSort(arr, low, pivot-1);
    // 递归排序基准元素右侧的子数组
    quickSort(arr, pivot+1, high);
}

int main() {
    // 测试数组
    int arr[10] = {22,11,1,67,56,32,16,98,20,4};

    // 调用快速排序函数
    quickSort(arr, 0, 9);

    // 输出排序结果
    for (int i = 0; i < 10; i++)
        printf("%d ", arr[i]);

    return 0;
}