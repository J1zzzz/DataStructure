# 逆拓扑排序实现文档（基于DFS算法）

## 一、算法概述
逆拓扑排序（Reverse Topological Sorting）是对有向无环图（DAG）的顶点进行排序的一种算法，其结果与拓扑排序顺序相反。在逆拓扑排序中，每个节点的所有后继节点都会出现在该节点之前。本实现基于深度优先搜索（DFS）算法，通过后序遍历来生成逆拓扑序列，时间复杂度为O(V+E)，其中V为顶点数，E为边数。

## 二、功能特点
1. **邻接表存储**：使用邻接表表示图结构，适合稀疏图
2. **深度优先搜索**：通过DFS后序遍历来生成逆拓扑序列
3. **内存管理**：提供图内存释放函数，避免内存泄漏
4. **结果存储**：将逆拓扑排序结果存储在数组中，便于后续处理

## 三、代码结构
```c
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// 邻接表节点结构
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

// 图结构
typedef struct {
    Node* adj[MAX_VERTICES];  // 邻接表
    int V;                    // 顶点数
    int visited[MAX_VERTICES]; // 访问标记数组
    int result[MAX_VERTICES];  // 存储逆拓扑排序结果
    int resultIndex;          // 结果数组索引
} Graph;

// 核心函数声明
Graph* createGraph(int vertices);     // 创建图
void addEdge(Graph* graph, int u, int v); // 添加边
void dfs(Graph* graph, int v);        // 深度优先搜索
int reverseTopologicalSort(Graph* graph); // 逆拓扑排序
void freeGraph(Graph* graph);          // 释放图内存
```

## 四、核心函数解析
### 1. `dfs(Graph* graph, int v)`
- **功能**：从顶点v开始进行深度优先搜索
- **参数**：
  - `graph`：图结构体指针
  - `v`：当前搜索的顶点
- **操作**：
  - 标记顶点v为已访问
  - 递归访问v的所有邻接顶点
  - 将顶点v加入结果数组（后序遍历）

### 2. `reverseTopologicalSort(Graph* graph)`
- **功能**：执行逆拓扑排序
- **参数**：
  - `graph`：图结构体指针
- **返回值**：1表示排序成功（本实现默认图为DAG，未检测环）
- **算法流程**：
  1. 初始化所有顶点为未访问状态
  2. 对每个顶点调用DFS（如果未被访问过）
  3. 结果数组中的顺序即为逆拓扑排序

### 3. 结果处理
逆拓扑排序结果存储在`graph->result`数组中，顺序为DFS后序遍历的顺序。若需要获得标准拓扑排序，需将结果数组反转。

## 五、使用示例
### 输入图结构（示例）
```c
Graph* graph = createGraph(6); // 6个顶点
addEdge(graph, 2, 5);  // 2→5
addEdge(graph, 0, 5);  // 0→5
addEdge(graph, 0, 4);  // 0→4
addEdge(graph, 1, 4);  // 1→4
addEdge(graph, 3, 2);  // 3→2
addEdge(graph, 1, 3);  // 1→3
```
该图表示的依赖关系如下（注意与拓扑排序示例中的边方向相反）：
- 节点2依赖于5
- 节点0依赖于5
- 节点0依赖于4
- 节点1依赖于4
- 节点3依赖于2
- 节点1依赖于3

### 输出结果
```c
// 逆拓扑排序结果（后序遍历顺序）
printf("逆拓扑排序结果：");
for (int i = graph->resultIndex - 1; i >= 0; i--) {
    printf("%d ", graph->result[i]);
}
// 输出：1 3 0 4 2 5 
// 对应的标准拓扑排序为：5 2 4 0 3 1
```

## 六、注意事项
1. **图类型限制**：本算法仅适用于有向无环图（DAG）。若图中存在环，结果将不正确。
2. **顶点编号**：顶点编号必须为0到MAX_VERTICES-1之间的整数。
3. **内存管理**：使用完图后需调用`freeGraph`释放内存，避免内存泄漏。
4. **结果反转**：若需要标准拓扑排序，需将结果数组反转。

## 七、扩展应用
1. **任务调度**：在某些场景下，需要按照逆依赖顺序执行任务
2. **编译系统**：确定编译模块的顺序，确保依赖项先被编译
3. **电路设计**：确定信号传播路径的逆序
4. **版本控制**：确定代码提交的逆序依赖关系

如需处理包含环的图，可扩展此算法以检测环的存在并给出相应提示。