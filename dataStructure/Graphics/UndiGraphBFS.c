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

// 队列结构，用于广度优先遍历
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

// 创建队列
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
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

// 广度优先遍历
void BFS(Graph* graph, int startVertex) {
    int visited[graph->numVertices];
    for (int i = 0; i < graph->numVertices; i++) {
        visited[i] = 0; // 初始化所有顶点为未访问
    }

    Queue* queue = createQueue(graph->numVertices);

    visited[startVertex] = 1; // 标记起始顶点为已访问
    enqueue(queue, startVertex);

    while (!isQueueEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        Node* temp = graph->adjLists[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
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

    printf("BFS starting from vertex 0: ");
    BFS(graph, 0);
    printf("\n");

    return 0;
}