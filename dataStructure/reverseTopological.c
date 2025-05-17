//
// Created by 86152 on 2025/5/18.
//
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node* adj[MAX_VERTICES];
    int V;
    int visited[MAX_VERTICES];
    int result[MAX_VERTICES];
    int resultIndex;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int vertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = vertices;
    graph->resultIndex = 0;

    for (int i = 0; i < vertices; i++) {
        graph->adj[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(Graph* graph, int u, int v) {
    Node* newNode = createNode(v);
    newNode->next = graph->adj[u];
    graph->adj[u] = newNode;
}

// 深度优先搜索递归函数
void dfs(Graph* graph, int v) {
    graph->visited[v] = 1; // 标记当前节点为已访问

    // 递归访问所有邻接节点
    Node* temp = graph->adj[v];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex]) {
            dfs(graph, adjVertex);
        }
        temp = temp->next;
    }

    // 将当前节点加入结果数组（逆拓扑顺序）
    graph->result[graph->resultIndex++] = v;
}

// 逆拓扑排序主函数
int reverseTopologicalSort(Graph* graph) {
    // 初始化所有节点为未访问
    for (int i = 0; i < graph->V; i++) {
        graph->visited[i] = 0;
    }

    // 对每个节点执行DFS（如果未被访问过）
    for (int i = 0; i < graph->V; i++) {
        if (!graph->visited[i]) {
            dfs(graph, i);
        }
    }

    return 1; // 逆拓扑排序成功
}

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

    // 添加边（注意：与拓扑排序示例中的边方向相反）
    addEdge(graph, 2, 5);
    addEdge(graph, 0, 5);
    addEdge(graph, 0, 4);
    addEdge(graph, 1, 4);
    addEdge(graph, 3, 2);
    addEdge(graph, 1, 3);

    // 执行逆拓扑排序
    if (reverseTopologicalSort(graph)) {
        printf("逆拓扑排序结果：");
        for (int i = graph->resultIndex - 1; i >= 0; i--) {
            printf("%d ", graph->result[i]);
        }
        printf("\n");
    }

    // 释放内存
    freeGraph(graph);

    return 0;
}