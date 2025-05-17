# 弗洛伊德算法实现文档

## 一、算法概述
弗洛伊德算法（Floyd-Warshall Algorithm）是一种用于计算图中所有节点对之间最短路径的经典算法。该算法能够处理有向图和无向图，并且允许图中存在负权边，但不能处理包含负权环的图。其时间复杂度为O(V³)，其中V是图中顶点的数量，因此适用于中小规模的图结构分析。

## 二、功能特点
1. 使用邻接矩阵表示图结构，便于初始化和操作
2. 通过动态规划的思想，逐步优化所有节点对之间的最短路径
3. 能够检测图中是否存在负权环，并在存在时给出提示
4. 输出完整的最短路径矩阵，直观展示任意两节点间的最短距离

## 三、代码结构
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define MAX_VERTICES 100

// 弗洛伊德算法核心实现
void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int V);

int main() {
    // 初始化图的邻接矩阵
    int V = 4;
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    // 调用算法计算最短路径
    floydWarshall(graph, V);

    return 0;
}
```

## 四、核心函数解析
### 1. 函数原型
```c
void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int V);
```
- **参数说明**：
    - `graph`：二维数组，表示图的邻接矩阵
    - `V`：图中顶点的数量

### 2. 算法流程
1. **初始化距离矩阵**：将初始距离矩阵设为输入图的邻接矩阵
2. **动态规划迭代**：
   ```c
   for (k = 0; k < V; k++) {
       for (i = 0; i < V; i++) {
           for (j = 0; j < V; j++) {
               if (dist[i][k] != INF && dist[k][j] != INF && 
                   dist[i][k] + dist[k][j] < dist[i][j]) {
                   dist[i][j] = dist[i][k] + dist[k][j];
               }
           }
       }
   }
   ```
   对于每对节点(i,j)，检查是否存在中间节点k使得路径i→k→j比当前记录的路径更短
3. **负权环检测**：检查每个节点到自身的距离是否为负
4. **输出结果**：打印所有节点对之间的最短路径矩阵

## 五、使用示例
### 输入图结构
```c
int graph[MAX_VERTICES][MAX_VERTICES] = {
    {0, 5, INF, 10},
    {INF, 0, 3, INF},
    {INF, INF, 0, 1},
    {INF, INF, INF, 0}
};
```
这个邻接矩阵表示的图有4个节点，边的权重如下：
- 节点0到节点1的距离为5
- 节点1到节点2的距离为3
- 节点2到节点3的距离为1
- 其他不可直接到达的节点间距离为无穷大(INF)

### 输出结果
```
所有节点对之间的最短路径矩阵：
0       5       8       9
INF     0       3       4
INF     INF     0       1
INF     INF     INF     0
```

## 六、注意事项
1. 代码中使用`INT_MAX`表示无穷大，在实际应用中需注意整数溢出问题
2. 图的最大顶点数由`MAX_VERTICES`宏定义控制，可根据需要调整
3. 该实现假设输入的图不包含负权环，算法会检测负权环并给出提示
4. 对于大规模图（顶点数超过100），建议优化内存使用或考虑其他算法

## 七、扩展应用
该算法可用于：
- 网络路由中的最短路径计算
- 社交网络中的最短关系路径分析
- 地图应用中的多目的地路径规划
- 电路设计中的信号传播延迟计算

如需处理大规模图数据，可考虑使用并行计算或分布式实现来优化性能。