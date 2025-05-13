//
// Created by 86152 on 2025/5/14.
//
#include <stdio.h>
#include <stdlib.h>

// 定义边的结构
typedef struct {
    int src, dest, weight;
} Edge;

// 定义图的结构
typedef struct {
    int V, E;  // 顶点数和边数
    Edge* edges;  // 边的数组
} Graph;

// 创建图
Graph* createGraph(int V, int E) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->E = E;
    graph->edges = (Edge*)malloc(E * sizeof(Edge));
    return graph;
}

// 释放图的内存
void destroyGraph(Graph* graph) {
    free(graph->edges);
    free(graph);
}

// 比较函数，用于qsort排序边
int compareEdges(const void* a, const void* b) {
    Edge* edge1 = (Edge*)a;
    Edge* edge2 = (Edge*)b;
    return edge1->weight - edge2->weight;
}

// 并查集数据结构的查找操作（带路径压缩）
int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}

// 并查集数据结构的合并操作（按秩合并）
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

// Kruskal算法实现
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

// 示例使用
int main() {
    /* 创建以下无向图
       0
      |  \
     10   6
      |     \
      1---5---2
    */
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

    // 计算最小生成树
    kruskalMST(graph);

    // 释放内存
    destroyGraph(graph);

    return 0;
}
