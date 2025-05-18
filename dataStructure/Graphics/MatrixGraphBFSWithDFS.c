//
// Created by 86152 on 2025/5/12.
//
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100 // 最大顶点数

// 定义图的结构
typedef struct {
    int numVertices; // 顶点数量
    int adjMatrix[MAX_VERTICES][MAX_VERTICES]; // 邻接矩阵
} Graph;
// 创建图
Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = vertices;

    // 初始化邻接矩阵
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph->adjMatrix[i][j] = 0; // 0表示没有边
        }
    }

    return graph;
}
// 添加边
void addEdge(Graph* graph, int src, int dest) {
    // 无向图：邻接矩阵是对称的
    graph->adjMatrix[src][dest] = 1;
    graph->adjMatrix[dest][src] = 1;
}
// 深度优先遍历的递归函数
void DFSUtil(Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1; // 标记当前顶点为已访问
    printf("%d ", vertex); // 输出当前顶点

    for (int i = 0; i < graph->numVertices; i++) {
        if (graph->adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFSUtil(graph, i, visited); // 递归访问邻接点
        }
    }
}

// 深度优先遍历
void DFS(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0}; // 初始化所有顶点为未访问
    DFSUtil(graph, startVertex, visited);
}
// 队列结构，用于广度优先遍历
typedef struct {
    int front, rear, size;
    unsigned capacity;
    int array[MAX_VERTICES];
} Queue;

// 创建队列
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    return queue;
}

// 队列是否为空
int isQueueEmpty(Queue* queue) {
    return (queue->size == 0);
}

// 入队操作
void enqueue(Queue* queue, int vertex) {
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = vertex;
    queue->size++;
}

// 出队操作
int dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return item;
}

// 广度优先遍历
void BFS(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0}; // 初始化所有顶点为未访问
    Queue* queue = createQueue(graph->numVertices);

    visited[startVertex] = 1; // 标记起始顶点为已访问
    enqueue(queue, startVertex);

    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->numVertices; i++) {
            if (graph->adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
}
int main() {
    Graph* graph = createGraph(6); // 创建一个包含6个顶点的图
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 5);

    printf("DFS starting from vertex 0: ");
    DFS(graph, 0);
    printf("\n");

    printf("BFS starting from vertex 0: ");
    BFS(graph, 0);
    printf("\n");

    return 0;
}