//
// Created by 86152 on 2025/5/12.
//
#include <stdio.h>
#include <stdlib.h>

// 定义图的结构
typedef struct Node {
    int vertex; // 顶点编号
    struct Node* next; // 指向下一个邻接点的指针
} Node;

typedef struct Graph {
    int numVertices; // 顶点数量
    Node** adjLists; // 邻接表数组
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
    graph->numVertices = vertices;

    // 创建邻接表数组
    graph->adjLists = (Node**)malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}

// 添加边
void addEdge(Graph* graph, int src, int dest) {
    // 添加从src到dest的边
    Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    // 添加从dest到src的边（因为是无向图）
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

// 深度优先遍历的递归函数
void DFSUtil(Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1; // 标记当前顶点为已访问
    printf("%d ", vertex); // 输出当前顶点

    Node* temp = graph->adjLists[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            DFSUtil(graph, adjVertex, visited); // 递归访问邻接点
        }
        temp = temp->next;
    }
}

// 深度优先遍历
void DFS(Graph* graph, int startVertex) {
    int visited[graph->numVertices];
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0; // 初始化所有顶点为未访问
    }

    DFSUtil(graph, startVertex, visited); // 调用递归函数
}

int main() {
    Graph* graph = createGraph(6); // 创建一个包含6个顶点的图
    addEdge(graph, 0, 2);
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    printf("DFS starting from vertex 1: ");
    DFS(graph, 1);
    printf("\n");

    return 0;
}