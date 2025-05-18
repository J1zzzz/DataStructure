//
// Created by 86152 on 2025/5/19.
//
#include <stdio.h>
#include <stdlib.h>

// 索引表结构
typedef struct {
    int max_key;  // 块内最大关键字
    int start;    // 块的起始位置
    int end;      // 块的结束位置
} IndexBlock;

// 分块查找函数
int blockSearch(int arr[], IndexBlock index[], int n, int m, int target) {
    // 1. 确定目标可能所在的块
    int block_idx = -1;
    for (int i = 0; i < m; i++) {
        if (target <= index[i].max_key) {
            block_idx = i;
            break;
        }
    }

    if (block_idx == -1) {
        return -1;  // 目标值超出所有块的范围
    }

    // 2. 在确定的块内进行顺序查找
    int start = index[block_idx].start;
    int end = index[block_idx].end;

    for (int i = start; i <= end; i++) {
        if (arr[i] == target) {
            return i;  // 找到目标值，返回索引
        }
    }

    return -1;  // 未找到目标值
}

// 示例主函数
int main() {
    // 待查找的有序数组
    int arr[] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80};
    int n = sizeof(arr) / sizeof(arr[0]);

    // 建立索引表（假设分为3块）
    IndexBlock index[3] = {
        {25, 0, 3},    // 第一块：最大值25，范围索引0-3
        {50, 4, 8},    // 第二块：最大值50，范围索引4-8
        {80, 9, 14}    // 第三块：最大值80，范围索引9-14
    };
    int m = 3;  // 块的数量

    // 测试查找
    int target = 45;
    int result = blockSearch(arr, index, n, m, target);

    if (result != -1) {
        printf("找到目标值 %d，索引位置为 %d\n", target, result);
    } else {
        printf("未找到目标值 %d\n", target);
    }

    return 0;
}