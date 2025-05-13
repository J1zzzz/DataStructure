# Dijkstra 算法实现单源最短路径（C语言）

## 项目简介
本项目实现了 Dijkstra 算法，用于求解无向图或有向图中从单个源点到所有其他顶点的最短路径。Dijkstra 算法通过优先队列（最小堆）来高效地选择当前距离最小的顶点，并逐步更新其邻接顶点的距离。

## 核心代码解释

### 图的结构定义
```c
typedef struct {
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
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
            if (i == j)
                graph->adj[i][j] = 0;
            else
                graph->adj[i][j] = INF;
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
}
```
- 在邻接矩阵中设置顶点 `src` 到顶点 `dest` 的边的权值为 `weight`。
- **注意**：如果图是有向图，只需设置 `adj[src][dest]`；如果是无向图，还需要设置 `adj[dest][src]`。

### 优先队列的实现
#### 节点结构
```c
typedef struct {
    int vertex;
    int distance;
} Node;
```
- `vertex` 表示顶点编号。
- `distance` 表示从源点到该顶点的当前距离。

#### 最小堆实现的优先队列
```c
typedef struct {
    Node* array;
    int size;
    int capacity;
} PriorityQueue;
```
- `array` 是一个动态数组，用于存储堆中的节点。
- `size` 表示当前堆的大小。
- `capacity` 表示堆的最大容量。

#### 创建优先队列
```c
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->array = (Node*)malloc(capacity * sizeof(Node));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}
```
- 分配内存创建一个新的优先队列对象。
- 初始化堆的大小为 `0`，并分配足够的空间。

#### 交换两个节点
```c
void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}
```
- 交换两个节点的内容，用于调整堆结构。

#### 最小堆化
```c
void minHeapify(PriorityQueue* pq, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < pq->size && pq->array[left].distance < pq->array[smallest].distance)
        smallest = left;

    if (right < pq->size && pq->array[right].distance < pq->array[smallest].distance)
        smallest = right;

    if (smallest != idx) {
        swap(&pq->array[smallest], &pq->array[idx]);
        minHeapify(pq, smallest);
    }
}
```
- 确保以 `idx` 为根的子树满足最小堆性质。
- 如果左子节点或右子节点的 `distance` 更小，则将它们与根节点交换，并递归调整子树。

#### 判断队列是否为空
```c
int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}
```
- 检查优先队列是否为空。

#### 提取最小值
```c
Node extractMin(PriorityQueue* pq) {
    if (pq->size <= 0) {
        Node empty = {-1, -1};
        return empty;
    }

    if (pq->size == 1) {
        pq->size--;
        return pq->array[0];
    }

    Node root = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    minHeapify(pq, 0);

    return root;
}
```
- 提取并返回堆顶节点（距离最小的节点）。
- 将最后一个节点移到堆顶，并调整堆结构。

#### 插入元素
```c
void insert(PriorityQueue* pq, int vertex, int distance) {
    pq->size++;
    int i = pq->size - 1;
    pq->array[i].vertex = vertex;
    pq->array[i].distance = distance;

    while (i != 0 && pq->array[(i - 1) / 2].distance > pq->array[i].distance) {
        swap(&pq->array[i], &pq->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}
```
- 将新节点插入堆中，并调整堆结构以保持最小堆性质。

### Dijkstra 算法实现
```c
void dijkstra(Graph* graph, int src) {
    int V = graph->vertices;
    int dist[V];      // 存储最短距离
    int sptSet[V];    // 标记顶点是否已处理

    // 初始化距离和标记数组
    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        sptSet[i] = 0;
    }

    // 源点到自身的距离为0
    dist[src] = 0;

    // 创建优先队列
    PriorityQueue* pq = createPriorityQueue(V);
    insert(pq, src, 0);

    // 处理每个顶点
    while (!isEmpty(pq)) {
        Node u = extractMin(pq);
        int vertex = u.vertex;

        // 如果顶点已处理，则跳过
        if (sptSet[vertex]) continue;

        sptSet[vertex] = 1;

        // 更新所有邻接顶点的距离
        for (int v = 0; v < V; v++) {
            if (!sptSet[v] && graph->adj[vertex][v] != INF &&
                dist[vertex] != INF && dist[vertex] + graph->adj[vertex][v] < dist[v]) {
                dist[v] = dist[vertex] + graph->adj[vertex][v];
                insert(pq, v, dist[v]);
            }
        }
    }

    // 打印最短路径结果
    printf("源点 %d 到各顶点的最短距离:\n", src);
    for (int i = 0; i < V; i++) {
        printf("到顶点 %d 的距离: ", i);
        if (dist[i] == INF)
            printf("INF\n");
        else
            printf("%d\n", dist[i]);
    }

    free(pq->array);
    free(pq);
}
```
- **初始化**：
    - `dist` 数组初始化为 `INF`，表示所有顶点的初始距离为无穷大。
    - `sptSet` 数组初始化为 `0`，表示所有顶点尚未处理。
    - 源点到自身的距离设置为 `0`。
- **优先队列**：
    - 创建一个优先队列，用于存储当前距离最小的顶点。
    - 将源点插入优先队列。
- **处理顶点**：
    - 每次从优先队列中提取距离最小的顶点。
    - 如果该顶点已处理，则跳过。
    - 更新该顶点的所有邻接顶点的距离，如果找到更短的路径，则更新 `dist` 数组，并将邻接顶点插入优先队列。
- **打印结果**：
    - 输出从源点到每个顶点的最短距离。

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
addEdge(graph, 0, 1, 4);
addEdge(graph, 0, 2, 2);
addEdge(graph, 1, 2, 5);
addEdge(graph, 1, 3, 10);
addEdge(graph, 2, 3, 3);
addEdge(graph, 3, 4, 7);
```

### 输出
```
源点 0 到各顶点的最短距离:
到顶点 0 的距离: 0
到顶点 1 的距离: 4
到顶点 2 的距离: 2
到顶点 3 的距离: 5
到顶点 4 的距离: 12
```

## 使用说明
1. 编译代码：
   ```bash
   gcc -o dijkstra dijkstra.c
   ```
2. 运行程序：
   ```bash
   ./dijkstra
   ```
3. 观察输出的从源点到每个顶点的最短距离。

## 注意事项
- 本代码假设图中边的权值为非负整数。
- 图的顶点数量不能超过 `MAX_VERTICES` 定义的值（默认为100）。
- 如果图中有孤立顶点或不连通的子图，Dijkstra 算法可能无法找到路径，输出的距离为 `INF`。
- 如果图中有负权边，Dijkstra 算法可能无法正确工作，需要使用 Bellman-Ford 算法来处理。