# Prim 算法实现最小生成树（C语言）

## 项目简介
本项目实现了基于图的邻接矩阵表示的 Prim 算法，用于求解无向图的最小生成树。代码通过创建图、添加边、运行 Prim 算法并打印最小生成树的边，展示了最小生成树的构建过程。

## 核心代码解释

### 图的结构定义
```c
typedef struct {
    int vertices; // 图的顶点数量
    int adj[MAX_VERTICES][MAX_VERTICES]; // 邻接矩阵，存储顶点之间的边权值
} Graph;
```
- `vertices` 表示图中的顶点数量。
- `adj` 是一个二维数组，用于存储图的邻接矩阵。`adj[i][j]` 表示顶点 `i` 到顶点 `j` 的边的权值。如果顶点之间没有边，则用 `INF`（表示无穷大）填充。

### 创建图
```c
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adj[i][j] = (i == j) ? 0 : INF;
        }
    }
    return graph;
}
```
- 分配内存创建一个新的图对象。
- 初始化邻接矩阵：
    - 对角线上的元素（`i == j`）设置为 `0`，表示顶点到自身的距离为 `0`。
    - 其他元素设置为 `INF`，表示顶点之间尚未连接。

### 添加边
```c
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adj[src][dest] = weight;
    graph->adj[dest][src] = weight;
}
```
- 在邻接矩阵中设置顶点 `src` 到顶点 `dest` 的边的权值为 `weight`。
- 因为是无向图，所以同时设置 `adj[dest][src]` 为相同的权值。

### Prim 算法实现
```c
void primMST(Graph* graph) {
    int vertices = graph->vertices;
    int parent[vertices];     // 存储最小生成树的父节点
    int key[vertices];        // 存储顶点到MST的最小权值
    int mstSet[vertices];     // 标记顶点是否已加入MST

    // 初始化
    for (int i = 0; i < vertices; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    // 从顶点0开始
    key[0] = 0;
    parent[0] = -1;  // 根节点没有父节点

    // 构建MST，包含所有顶点
    for (int count = 0; count < vertices - 1; count++) {
        // 找到未包含在MST中且key值最小的顶点
        int min = INF, min_index;
        for (int v = 0; v < vertices; v++) {
            if (mstSet[v] == 0 && key[v] < min) {
                min = key[v];
                min_index = v;
            }
        }

        // 将找到的顶点加入MST
        mstSet[min_index] = 1;

        // 更新与该顶点相邻的所有顶点的key值和parent
        for (int v = 0; v < vertices; v++) {
            if (graph->adj[min_index][v] && mstSet[v] == 0 &&
                graph->adj[min_index][v] < key[v]) {
                parent[v] = min_index;
                key[v] = graph->adj[min_index][v];
            }
        }
    }

    // 打印最小生成树
    printf("Edge \tWeight\n");
    for (int i = 1; i < vertices; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph->adj[i][parent[i]]);
    }
}
```
- **初始化**：
    - `key` 数组初始化为 `INF`，表示所有顶点到最小生成树的初始距离为无穷大。
    - `mstSet` 数组初始化为 `0`，表示所有顶点尚未加入最小生成树。
    - 从顶点 `0` 开始，将其 `key` 值设置为 `0`，并将其父节点设置为 `-1`（根节点没有父节点）。
- **构建最小生成树**：
    - 每次从未加入最小生成树的顶点中找到 `key` 值最小的顶点，将其加入最小生成树。
    - 更新与该顶点相邻的所有顶点的 `key` 值和 `parent` 值，确保它们到最小生成树的最短距离被记录。
- **打印结果**：
    - 遍历 `parent` 数组，打印最小生成树的边及其权重。

### 释放图的内存
```c
void destroyGraph(Graph* graph) {
    free(graph);
}
```
- 释放图对象所占用的内存，避免内存泄漏。

## 示例运行
### 输入
```c
// 创建一个包含5个顶点的图
Graph* graph = createGraph(5);

// 添加边
addEdge(graph, 0, 1, 2);
addEdge(graph, 0, 3, 6);
addEdge(graph, 1, 2, 3);
addEdge(graph, 1, 3, 8);
addEdge(graph, 1, 4, 5);
addEdge(graph, 2, 4, 7);
addEdge(graph, 3, 4, 9);
```

### 输出
```
最小生成树的边为:
Edge 	Weight
0 - 1 	2
1 - 2 	3
1 - 4 	5
0 - 3 	6
```

## 使用说明
1. 编译代码：
   ```bash
   gcc -o prim prim.c
   ```
2. 运行程序：
   ```bash
   ./prim
   ```
3. 观察输出的最小生成树的边及其权重。

## 注意事项
- 本代码假设图是无向图，且边的权值为非负整数。
- 图的顶点数量不能超过 `MAX_VERTICES` 定义的值（默认为100）。
- 如果图中有孤立顶点或不连通的子图，Prim 算法可能无法正确处理，需要在实际应用中根据具体需求调整代码逻辑。