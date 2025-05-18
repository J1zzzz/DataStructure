# 二分查找算法（C语言实现）

## 简介

本项目实现了二分查找（Binary Search）算法的两种常见形式：迭代法和递归法。二分查找是一种高效的搜索算法，适用于已排序的数组，时间复杂度为O(log n)。

## 算法原理

二分查找的核心思想是将目标值与数组中间元素进行比较：
- 如果相等，则找到目标
- 如果目标值小于中间元素，则在左半部分继续查找
- 如果目标值大于中间元素，则在右半部分继续查找

每次比较都能将搜索范围缩小一半，因此效率极高。

## 代码结构

```c
// 迭代实现的二分查找
int binarySearch_iterative(int arr[], int left, int right, int target);

// 递归实现的二分查找
int binarySearch_recursive(int arr[], int left, int right, int target);
```

## 特性

1. **防止整数溢出**：计算中间索引时使用`left + (right - left) / 2`，而非`(left + right) / 2`
2. **两种实现方式**：同时提供迭代和递归版本，便于理解和应用
3. **边界安全**：严格检查搜索范围，避免越界访问
4. **返回值明确**：找到目标时返回索引，未找到时返回-1

## 使用方法

### 前提条件
- 待搜索的数组必须是**有序的**
- 调用时需提供正确的数组边界（left和right）

### 示例代码
```c
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
```

## 复杂度分析

| 指标        | 迭代实现 | 递归实现 |
|-------------|----------|----------|
| 时间复杂度  | O(log n) | O(log n) |
| 空间复杂度  | O(1)     | O(log n) |

递归实现的空间复杂度较高，主要由于递归调用栈的深度。

## 注意事项

1. **数组必须有序**：二分查找的前提是数组已按升序排列
2. **参数合法性**：确保`left`和`right`参数在有效范围内（0到数组长度-1）
3. **重复元素**：如果数组中有重复元素，本实现不保证返回第一个或最后一个匹配位置

## 应用场景

- 已排序数组的快速查找
- 优化需要频繁查找操作的算法
- 作为其他复杂算法的基础组件

## 扩展建议

1. 如需查找第一个或最后一个匹配位置，可对算法进行扩展
2. 对于浮点数数组，需考虑精度问题
3. 可添加错误处理机制，增强代码健壮性