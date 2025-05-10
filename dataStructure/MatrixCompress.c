#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxVertexNum 100   // 顶点数目最大值
#define INF 32767          // 表示无穷大

typedef char VertexType;   // 顶点的数据类型
typedef int EdgeType;      // 带权图中边上权值的数据类型

typedef struct {
    VertexType Vex[MaxVertexNum];   // 顶点表
    EdgeType Edge[(MaxVertexNum * (MaxVertexNum - 1)) / 2];  // 压缩存储的邻接矩阵
    int vexnum, edgenum;    // 图的顶点数和边数
    int adjIndex[MaxVertexNum + 1];  // 压缩矩阵索引，用于快速定位每一行的起始位置
} MGraph;

/********** 创建无向图 ********/
void create_Graph(MGraph *G) {
    int i, j, k = 0;
    int start, end;  // 边的起点序号、终点序号
    int w;           // 边上的权值
    printf("请输入所创建无向图的顶点数和边数(用空格隔开): ");
    if (scanf("%d %d", &G->vexnum, &G->edgenum) != 2 || G->vexnum <= 0 || G->edgenum < 0) {
        printf("%d",G->vexnum);
        printf("输入的顶点数或边数不合法。\n");
        exit(1);
    }

    for ( i=0;i<MaxVertexNum;i++) {
        G->adjIndex[i] = i-1;
    }

    // 初始化压缩矩阵索引
    for (i = 1; i <= G->vexnum; i++) {
        G->adjIndex[i] = G->adjIndex[i - 1] + i;
    }

    // 图的初始化
    for (i = 0; i < G->adjIndex[G->vexnum]; i++) {
        G->Edge[i] = INF;
    }

    // 顶点信息存入顶点表
    for (i = 0; i < G->vexnum; i++) {
        printf("请输入第 %d 个顶点的信息: ", i + 1);
        if (scanf(" %c", &G->Vex[i]) != 1) {
            printf("输入的顶点信息不合法。\n");
            exit(1);
        }
    }
    printf("\n");

    // 输入无向图边的信息
    for (i = 0; i < G->edgenum; i++) {
        printf("请输入边的起点序号，终点序号，权值(用空格隔开): ");
        if (scanf("%d %d %d", &start, &end, &w) != 3 || start < 1 || start > G->vexnum || end < 1 || end > G->vexnum || w < 0) {
            printf("输入的边信息不合法。\n");
            exit(1);
        }
        if (start > end) {  // 确保 start <= end
            int temp = start;
            start = end;
            end = temp;
        }
        j = G->adjIndex[start] + end - start - 1;
        G->Edge[j] = w;
    }
}

/*********** 打印出邻接矩阵 *********/
void print_Matrix(MGraph G) {
    int i, j, e;
    printf("\n图的顶点为: ");
    for (i = 0; i < G.vexnum; i++)
        printf("%c ", G.Vex[i]);
    printf("\n输出邻接矩阵:\n");

    // 打印表头
    printf("\t");
    for (i = 0; i < G.vexnum; i++)
        printf("\t\t%c", G.Vex[i]);
    printf("\n");

    // 打印邻接矩阵
    for (i = 0; i < G.vexnum; i++) {
        printf("\t%c", G.Vex[i]); // 打印行标题
        for (j = 0; j < G.vexnum; j++) {
            if (j < i) {
                e = G.adjIndex[i] + j;
            } else if (j == i) {
                printf("\t\t0");
                continue;
            } else {
                e = G.adjIndex[i] + (j - i);
            }
            if (G.Edge[e] == INF)
                printf("\t\t∞");
            else
                printf("\t\t%d", G.Edge[e]);
        }
        printf("\n");
    }
}

int main() {
    MGraph G;
    create_Graph(&G);
    print_Matrix(G);
    return 0;
}