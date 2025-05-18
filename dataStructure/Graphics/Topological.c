//
// Created by 86152 on 2025/5/18.
//
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
    Node* adj[MAX_VERTICES];
    int inDegree[MAX_VERTICES];
    int V; // 顶点数
} Graph;

// 创建新节点
Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// 创建图
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = vertices;

    for (int i = 0; i < vertices; i++) {
        graph->adj[i] = NULL;
        graph->inDegree[i] = 0;
    }

    return graph;
}

// 添加边 (u -> v)
void addEdge(Graph* graph, int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;
    graph->inDegree[v]++;
}

// 拓扑排序
int topologicalSort(Graph* graph, int* order) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    int count = 0;

    // 将所有入度为0的顶点入队
    for (int i = 0; i < graph->V; i++) {
        if (graph->inDegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    // 处理队列中的每个顶点
    while (front < rear) {
        int u = queue[front++];
        order[count++] = u;

        // 遍历u的所有邻接顶点
        Node* temp = graph->adj[u];
        while (temp != NULL) {
            int v = temp->vertex;
            // 减少邻接顶点的入度
            if (--graph->inDegree[v] == 0) {
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }

    // 检查是否存在环
    if (count != graph->V) {
        printf("图中存在环，无法进行拓扑排序！\n");
        return 0; // 排序失败
    }

    return 1; // 排序成功
}

// 释放图内存
void freeGraph(Graph* graph) {
    for (int i = 0; i < graph->V; i++) {
        Node* temp = graph->adj[i];
        while (temp != NULL) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(graph);
}

int main() {
    // 创建一个有6个顶点的图
    Graph* graph = createGraph(6);

    // 添加边
    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    int order[MAX_VERTICES];

    // 执行拓扑排序
    if (topologicalSort(graph, order)) {
        printf("拓扑排序结果：");
        for (int i = 0; i < graph->V; i++) {
            printf("%d ", order[i]);
        }
        printf("\n");
    }

    // 释放内存
    freeGraph(graph);

    return 0;
}