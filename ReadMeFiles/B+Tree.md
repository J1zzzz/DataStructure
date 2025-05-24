# B+树C语言实现

## 概述
本项目实现了B+树数据结构的C语言版本，B+树是一种广泛应用于数据库和文件系统的平衡多路搜索树，支持高效的范围查询和随机访问。

## 功能特点
- 支持键的插入和查找操作
- 叶子节点形成有序链表，便于范围查询
- 自动维护树的平衡性，确保操作效率
- 内存管理安全，提供释放内存的函数

## 数据结构
B+树的节点结构定义如下：
```c
typedef struct BPlusTreeNode {
    bool is_leaf;          // 是否为叶子节点
    int num_keys;          // 当前键的数量
    int *keys;             // 键数组
    struct BPlusTreeNode **children;  // 子节点指针数组
    struct BPlusTreeNode *next;       // 叶子节点的下一个指针（用于链表）
} BPlusTreeNode;
```

## 核心操作
- `createNode`：创建新节点
- `search`：查找指定键
- `insert`：插入新键
- `insertNonFull`：在非满节点中插入键
- `splitChild`：分裂满节点
- `traverse`：按顺序遍历B+树
- `freeTree`：释放树的内存

## 使用方法
1. **编译运行**：
   ```bash
   gcc bplus_tree.c -o bplus_tree
   ./bplus_tree
   ```

2. **调整参数**：通过修改`ORDER`宏定义来调整B+树的阶数：
   ```c
   #define ORDER 4  // B+树的阶数，可根据需要调整
   ```

3. **示例代码**：
   ```c
   BPlusTreeNode* root = NULL;
   
   // 插入数据
   root = insert(root, 10);
   root = insert(root, 20);
   root = insert(root, 5);
   
   // 遍历B+树
   traverse(root);
   
   // 查找键
   printf("查找键 10: %s\n", search(root, 10) ? "找到" : "未找到");
   
   // 释放内存
   freeTree(root);
   ```

## 性能特点
- **插入操作**：O(log n)
- **查找操作**：O(log n)
- **范围查询**：O(log n + k)，k为结果数量

## 应用场景
- 数据库索引结构
- 文件系统索引
- 需要高效范围查询和随机访问的场景

## 扩展建议
1. 添加删除操作
2. 实现更复杂的查询功能
3. 添加持久化存储支持
4. 实现并发控制机制

## 注意事项
- 本实现未处理重复键的情况，如需支持可修改插入逻辑
- 对于大规模数据，建议适当增加ORDER值以减少树的高度
- 使用完毕后务必调用`freeTree`释放内存，防止内存泄漏

