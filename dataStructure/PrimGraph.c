//
// Created by 86152 on 2025/5/14.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 999999
#define MAX_VERTICES 100

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
            graph->adj[i][j] = (i == j) ? 0 : INF;
        }
    }
    return graph;
}

// 添加边
void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->adj[src][dest] = weight;
    graph->adj[dest][src] = weight;
}

// Prim 算法实现
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

// 释放图的内存
void destroyGraph(Graph* graph) {
    free(graph);
}

// 示例使用
int main() {
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

    // 计算最小生成树
    printf("最小生成树的边为:\n");
    primMST(graph);

    // 释放内存
    destroyGraph(graph);

    return 0;
}
