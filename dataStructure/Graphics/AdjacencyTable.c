//
// Created by 86152 on 2025/5/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxVertexNum 100
#define INF 32767

typedef char VertexType;
typedef int EdgeType;

typedef struct EdgeNode {
    int adjvex;           // 邻接点的序号
    int weight;           // 边的权值
    struct EdgeNode* next; // 指向下一个邻接点的指针
} EdgeNode;

typedef struct VertexNode {
    VertexType data;      // 顶点信息
    EdgeNode* firstedge;  // 指向第一个邻接点的指针
} VertexNode, ALGraph[MaxVertexNum];

/********** 创建无向图 ********/
void create_Graph(ALGraph G, int* vexnum, int* edgenum) {
    int i, j, k;
    int start, end;  // 边的起点序号、终点序号
    int w;           // 边上的权值
    EdgeNode* e1, * e2;

    printf("请输入所创建无向图的顶点数和边数(用空格隔开): ");
    if (scanf("%d %d", vexnum, edgenum) != 2 || *vexnum <= 0 || *edgenum < 0) {
        printf("输入的顶点数或边数不合法。\n");
        exit(1);
    }

    // 初始化顶点表
    for (i = 0; i < *vexnum; i++) {
        printf("请输入第 %d 个顶点的信息: ", i + 1);
        if (scanf(" %c", &G[i].data) != 1) {
            printf("输入的顶点信息不合法。\n");
            exit(1);
        }
        G[i].firstedge = NULL;
    }
    printf("\n");

    // 输入无向图边的信息
    for (k = 0; k < *edgenum; k++) {
        printf("请输入边的起点序号，终点序号，权值(用空格隔开): ");
        if (scanf("%d %d %d", &start, &end, &w) != 3 || start < 1 || start > *vexnum || end < 1 || end > *vexnum || w < 0) {
            printf("输入的边信息不合法。\n");
            exit(1);
        }
        start--;  // 转换为数组索引
        end--;

        // 创建边表节点
        e1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        e1->adjvex = end;
        e1->weight = w;
        e1->next = G[start].firstedge;
        G[start].firstedge = e1;

        e2 = (EdgeNode*)malloc(sizeof(EdgeNode));
        e2->adjvex = start;
        e2->weight = w;
        e2->next = G[end].firstedge;
        G[end].firstedge = e2;
    }
}

/*********** 打印邻接表 *********/
void print_Graph(ALGraph G, int vexnum) {
    int i;
    EdgeNode* p;

    printf("\n图的顶点为: ");
    for (i = 0; i < vexnum; i++)
        printf("%c ", G[i].data);
    printf("\n输出邻接表:\n");

    for (i = 0; i < vexnum; i++) {
        printf("%c: ", G[i].data);
        p = G[i].firstedge;
        while (p) {
            printf("%c(%d) -> ", G[p->adjvex].data, p->weight);
            p = p->next;
        }
        printf("NUll\n");
    }
}

int main() {
    ALGraph G;
    int vexnum, edgenum;
    create_Graph(G, &vexnum, &edgenum);
    print_Graph(G, vexnum);
    return 0;
}
