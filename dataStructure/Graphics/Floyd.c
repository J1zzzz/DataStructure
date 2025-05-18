//
// Created by 86152 on 2025/5/18.
//
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX
#define MAX_VERTICES 100

void floydWarshall(int graph[MAX_VERTICES][MAX_VERTICES], int V) {
    int dist[MAX_VERTICES][MAX_VERTICES];
    int i, j, k;

    // 初始化距离矩阵为输入图的邻接矩阵
    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // 动态规划计算最短路径
    for (k = 0; k < V; k++) {
        for (i = 0; i < V; i++) {
            for (j = 0; j < V; j++) {
                // 如果经过顶点k的路径更短，则更新dist[i][j]
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    }
            }
        }
    }

    // 检查负权环
    for (i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            printf("图包含负权环，无法计算最短路径！\n");
            return;
        }
    }

    // 输出结果
    printf("所有节点对之间的最短路径矩阵：\n");
    for (i = 0; i < V; i++) {
        for (j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", dist[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int V = 4; // 顶点数
    int graph[MAX_VERTICES][MAX_VERTICES] = {
        {0, 5, INF, 10},
        {INF, 0, 3, INF},
        {INF, INF, 0, 1},
        {INF, INF, INF, 0}
    };

    floydWarshall(graph, V);

    return 0;
}