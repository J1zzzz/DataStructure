//
// Created by 86152 on 2025/5/14.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// 图的邻接矩阵表示
typedef struct {
    int vertices;
    int adj[MAX_VERTICES][MAX_VERTICES];
} Graph;

// 创建图
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

// 添加边
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adj[src][dest] = weight;
}

// 优先队列节点结构
typedef struct {
    int vertex;
    int distance;
} Node;

// 最小堆实现的优先队列
typedef struct {
    Node* array;
    int size;
    int capacity;
} PriorityQueue;

// 创建优先队列
PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->array = (Node*)malloc(capacity * sizeof(Node));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

// 交换两个节点
void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

// 最小堆化
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

// 判断队列是否为空
int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

// 提取最小值
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

// 插入元素
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

// Dijkstra算法实现
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

// 释放图的内存
void destroyGraph(Graph* graph) {
    free(graph);
}

// 示例使用
int main() {
    // 创建一个包含5个顶点的图
    Graph* graph = createGraph(5);

    // 添加边
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 2);
    addEdge(graph, 1, 2, 5);
    addEdge(graph, 1, 3, 10);
    addEdge(graph, 2, 3, 3);
    addEdge(graph, 3, 4, 7);

    // 计算从顶点0出发的最短路径
    dijkstra(graph, 0);

    // 释放内存
    destroyGraph(graph);

    return 0;
}