//
// Created by 86152 on 2025/5/19.
//
#include <stdio.h>

// 迭代实现的二分查找
int binarySearch_iterative(int arr[], int left, int right, int target) {
    while (left <= right) {
        int mid = left + (right - left) / 2;  // 防止整数溢出

        if (arr[mid] == target)
            return mid;  // 找到目标值，返回索引

        if (arr[mid] < target)
            left = mid + 1;  // 目标在右半部分
        else
            right = mid - 1; // 目标在左半部分
    }

    return -1;  // 未找到目标值
}

// 递归实现的二分查找
int binarySearch_recursive(int arr[], int left, int right, int target) {
    if (left > right)
        return -1;  // 搜索范围无效，未找到

    int mid = left + (right - left) / 2;  // 防止整数溢出

    if (arr[mid] == target)
        return mid;  // 找到目标值

    if (arr[mid] < target)
        return binarySearch_recursive(arr, mid + 1, right, target);  // 右半部分递归
    else
        return binarySearch_recursive(arr, left, mid - 1, target);  // 左半部分递归
}

// 测试代码
int main() {
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 12;

    // 使用迭代方法查找
    int result_iterative = binarySearch_iterative(arr, 0, n - 1, target);
    if (result_iterative != -1)
        printf("迭代法找到 %d 在索引 %d 处\n", target, result_iterative);
    else
        printf("迭代法未找到 %d\n", target);

    // 使用递归方法查找
    int result_recursive = binarySearch_recursive(arr, 0, n - 1, target);
    if (result_recursive != -1)
        printf("递归法找到 %d 在索引 %d 处\n", target, result_recursive);
    else
        printf("递归法未找到 %d\n", target);

    return 0;
}