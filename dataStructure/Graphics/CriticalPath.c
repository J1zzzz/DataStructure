//
// Created by 86152 on 2025/5/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100
#define INF INT_MAX

// 边表节点
typedef struct EdgeNode {
    int adjvex;         // 邻接点域
    int weight;         // 边的权值
    struct EdgeNode* next; // 指向下一条边的指针
} EdgeNode;

// 顶点表节点
typedef struct VertexNode {
    int in;             // 入度
    int data;           // 顶点信息
    EdgeNode* firstedge; // 边表头指针
} VertexNode, AdjList[MAX_VERTICES];

// 图结构
typedef struct {
    AdjList adjList;
    int numVertices, numEdges; // 顶点数和边数
} Graph;

// 全局变量用于存储拓扑排序结果
int topOrder[MAX_VERTICES];
int ve[MAX_VERTICES]; // 事件最早发生时间
int vl[MAX_VERTICES]; // 事件最迟发生时间

// 创建图
Graph* createGraph(int numVertices, int numEdges) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;

    for (int i = 0; i < numVertices; i++) {
        graph->adjList[i].in = 0;
        graph->adjList[i].data = i;
        graph->adjList[i].firstedge = NULL;
    }

    return graph;
}

// 添加边
void addEdge(Graph* graph, int start, int end, int weight) {
    EdgeNode* edge = (EdgeNode*)malloc(sizeof(EdgeNode));
    edge->adjvex = end;
    edge->weight = weight;
    edge->next = graph->adjList[start].firstedge;
    graph->adjList[start].firstedge = edge;
    graph->adjList[end].in++;
}

// 拓扑排序，计算ve数组
int topologicalSort(Graph* graph) {
    int stack[MAX_VERTICES];
    int top = -1;
    int count = 0;

    // 初始化ve数组
    for (int i = 0; i < graph->numVertices; i++) {
        ve[i] = 0;
    }

    // 将入度为0的顶点入栈
    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjList[i].in == 0) {
            stack[++top] = i;
        }
    }

    while (top != -1) {
        int u = stack[top--];
        topOrder[count++] = u;

        EdgeNode* p = graph->adjList[u].firstedge;
        while (p != NULL) {
            int v = p->adjvex;
            if (--graph->adjList[v].in == 0) {
                stack[++top] = v;
            }
            // 更新ve[v]
            if (ve[u] + p->weight > ve[v]) {
                ve[v] = ve[u] + p->weight;
            }
            p = p->next;
        }
    }

    if (count < graph->numVertices) {
        printf("图中存在环！\n");
        return 0;
    }
    return 1;
}

// 计算关键路径
void criticalPath(Graph* graph) {
    if (!topologicalSort(graph)) return;

    int maxVe = 0;
    // 找出最大的ve值，即工程总时间
    for (int i = 0; i < graph->numVertices; i++) {
        if (ve[i] > maxVe) {
            maxVe = ve[i];
        }
    }

    // 初始化vl数组
    for (int i = 0; i < graph->numVertices; i++) {
        vl[i] = maxVe;
    }

    // 从后往前计算vl数组
    for (int i = graph->numVertices - 1; i >= 0; i--) {
        int u = topOrder[i];
        EdgeNode* p = graph->adjList[u].firstedge;
        while (p != NULL) {
            int v = p->adjvex;
            if (vl[v] - p->weight < vl[u]) {
                vl[u] = vl[v] - p->weight;
            }
            p = p->next;
        }
    }

    // 输出事件的最早和最迟开始时间
    printf("事件的最早和最迟开始时间：\n");
    printf("事件\t最早开始时间\t最迟开始时间\n");
    for (int i = 0; i < graph->numVertices; i++) {
        printf("%d\t%d\t\t%d\n", i, ve[i], vl[i]);
    }

    // 计算活动的最早和最迟开始时间
    printf("\n活动的最早和最迟开始时间：\n");
    printf("活动\t最早开始时间\t最迟开始时间\t松弛时间\n");
    for (int u = 0; u < graph->numVertices; u++) {
        EdgeNode* p = graph->adjList[u].firstedge;
        while (p != NULL) {
            int v = p->adjvex;
            int e = ve[u];             // 活动最早开始时间
            int l = vl[v] - p->weight; // 活动最迟开始时间
            int slack = l - e;         // 松弛时间

            printf("%d->%d\t%d\t\t%d\t\t%s\n",
                   u, v, e, l, slack == 0 ? "关键活动" : "非关键活动");
            p = p->next;
        }
    }

    // 输出关键路径
    printf("\n关键路径：\n");
    for (int u = 0; u < graph->numVertices; u++) {
        EdgeNode* p = graph->adjList[u].firstedge;
        while (p != NULL) {
            int v = p->adjvex;
            if (ve[u] == vl[v] - p->weight) {
                printf("%d->%d ", u, v);
            }
            p = p->next;
        }
    }
    printf("\n");
}

// 释放图内存
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        EdgeNode* p = graph->adjList[i].firstedge;
        while (p != NULL) {
            EdgeNode* temp = p;
            p = p->next;
            free(temp);
        }
    }
    free(graph);
}

int main() {
    // 示例：AOE网（顶点表示事件，边表示活动）
    Graph* graph = createGraph(9, 11);

    // 添加边（起点，终点，权值）
    addEdge(graph, 0, 1, 6);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 0, 3, 5);
    addEdge(graph, 1, 4, 1);
    addEdge(graph, 2, 4, 1);
    addEdge(graph, 3, 5, 2);
    addEdge(graph, 4, 6, 9);
    addEdge(graph, 4, 7, 7);
    addEdge(graph, 5, 7, 4);
    addEdge(graph, 6, 8, 2);
    addEdge(graph, 7, 8, 4);

    // 计算关键路径
    criticalPath(graph);

    // 释放内存
    freeGraph(graph);

    return 0;
}
