# Kruskal 算法实现最小生成树（C语言）

## 项目简介
本项目实现了 Kruskal 算法，用于求解无向图的最小生成树。Kruskal 算法通过按边的权重排序并逐步选择不形成环的边来构建最小生成树。代码中使用了并查集数据结构来高效地检测环。

## 核心代码解释

### 边和图的结构定义
```c
typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int V, E;  // 顶点数和边数
    Edge* edges;  // 边的数组
} Graph;
```
- `Edge` 结构体表示图中的一条边，包含起点 `src`、终点 `dest` 和权重 `weight`。
- `Graph` 结构体表示图，包含顶点数 `V`、边数 `E` 和边的数组 `edges`。

### 创建图
```c
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}
```
- 分配内存创建一个新的图对象。
- 初始化图的顶点数 `V` 和边数 `E`，并为边的数组分配内存。

### 释放图的内存
```c
void destroyGraph(Graph* graph) {
    free(graph->edges);
    free(graph);
}
```
- 释放边的数组和图对象所占用的内存，避免内存泄漏。

### 排序边
```c
int compareEdges(const void* a, const void* b) {
    Edge* edge1 = (Edge*)a;
    Edge* edge2 = (Edge*)b;
    return edge1->weight - edge2->weight;
}
```
- 比较函数，用于 `qsort` 排序边。
- 按边的权重从小到大排序。

### 并查集操作
#### 查找操作（带路径压缩）
```c
int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}
```
- 查找某个顶点的根节点。
- 如果当前节点不是根节点，则递归查找其父节点，并进行路径压缩（将当前节点直接连接到根节点）。

#### 合并操作（按秩合并）
```c
void unionSets(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}
```
- 合并两个集合。
- 比较两个根节点的秩（深度），将秩较小的集合合并到秩较大的集合中。
- 如果秩相同，则将一个集合合并到另一个集合中，并增加秩。

### Kruskal 算法实现
```c
void kruskalMST(Graph* graph) {
    int V = graph->V;
    Edge result[V];  // 存储最小生成树的边
    int e = 0;  // 结果数组的索引
    int i = 0;  // 已排序边的索引

    // 步骤1: 按权重升序排列边
    qsort(graph->edges, graph->E, sizeof(Edge), compareEdges);

    // 为并查集分配内存
    int* parent = (int*)malloc(V * sizeof(int));
    int* rank = (int*)malloc(V * sizeof(int));

    // 初始化并查集
    for (int v = 0; v < V; v++) {
        parent[v] = v;
        rank[v] = 0;
    }

    // 步骤2: 按顺序选择边
    while (e < V - 1 && i < graph->E) {
        Edge next_edge = graph->edges[i++];

        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);

        // 如果选择这条边不会形成环，则包含它
        if (x != y) {
            result[e++] = next_edge;
            unionSets(parent, rank, x, y);
        }
    }

    // 打印结果
    printf("最小生成树的边为:\n");
    for (i = 0; i < e; i++)
        printf("%d -- %d == %d\n", result[i].src, result[i].dest, result[i].weight);

    // 释放内存
    free(parent);
    free(rank);
}
```
- **排序边**：按边的权重从小到大排序。
- **初始化并查集**：每个顶点的父节点初始化为自身，秩初始化为 `0`。
- **选择边**：
  - 遍历排序后的边。
  - 使用并查集检测当前边是否会形成环（通过查找两个顶点的根节点是否相同）。
  - 如果不会形成环，则将该边加入最小生成树，并合并两个顶点所在的集合。
- **打印结果**：输出最小生成树的所有边及其权重。

## 示例运行
### 输入
```c
// 创建一个包含3个顶点和3条边的图
int V = 3;  // 3个顶点
int E = 3;  // 3条边
Graph* graph = createGraph(V, E);

// 添加边 0-1
graph->edges[0].src = 0;
graph->edges[0].dest = 1;
graph->edges[0].weight = 10;

// 添加边 0-2
graph->edges[1].src = 0;
graph->edges[1].dest = 2;
graph->edges[1].weight = 6;

// 添加边 1-2
graph->edges[2].src = 1;
graph->edges[2].dest = 2;
graph->edges[2].weight = 5;
```

### 输出
```
最小生成树的边为:
1 -- 2 == 5
0 -- 2 == 6
```

## 使用说明
1. 编译代码：
   ```bash
   gcc -o kruskal kruskal.c
   ```
2. 运行程序：
   ```bash
   ./kruskal
   ```
3. 观察输出的最小生成树的边及其权重。

## 注意事项
- 本代码假设图是无向图，且边的权值为非负整数。
- 图的顶点数和边数需要在创建图时正确设置。
- 如果图中有孤立顶点或不连通的子图，Kruskal 算法可能无法正确处理，需要在实际应用中根据具体需求调整代码逻辑。