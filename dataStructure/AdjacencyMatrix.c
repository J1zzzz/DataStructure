#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxVertexNum 100   // 顶点数目最大值
#define INF 32767          // 表示无穷大

typedef char VertexType;   // 顶点的数据类型
typedef int EdgeType;      // 带权图中边上权值的数据类型

typedef struct
{
    VertexType Vex[MaxVertexNum];   // 顶点表
    EdgeType Edge[MaxVertexNum][MaxVertexNum];  // 邻接矩阵，边表
    int vexnum, edgenum;    // 图的顶点数和边数
} MGraph;

/********** 创建无向图 **********/
void create_Graph(MGraph *G)
{
    int i, j;
    int start, end;  // 边的起点序号、终点序号
    int w;           // 边上的权值
    printf("请输入所创建无向图的顶点数和边数(用空格隔开): ");
    if (scanf("%d %d", &G->vexnum, &G->edgenum) != 2 || G->vexnum <= 0 || G->edgenum < 0)
    {
        printf("输入的顶点数或边数不合法。\n");
        exit(1);
    }

    printf("\n");
    // 图的初始化
    for (i = 0; i < G->vexnum; i++)
    {
        for (j = 0; j < G->vexnum; j++)
        {
            G->Edge[i][j] = (i == j) ? 0 : INF;
        }
    }

    // 顶点信息存入顶点表
    for (i = 0; i < G->vexnum; i++)
    {
        printf("请输入第 %d 个顶点的信息: ", i + 1);
        if (scanf(" %c", &G->Vex[i]) != 1)
        {
            printf("输入的顶点信息不合法。\n");
            exit(1);
        }
    }
    printf("\n");

    // 输入无向图边的信息
    for (i = 0; i < G->edgenum; i++)
    {
        printf("请输入边的起点序号，终点序号，权值(用空格隔开): ");
        if (scanf("%d %d %d", &start, &end, &w) != 3 || start < 1 || start > G->vexnum || end < 1 || end > G->vexnum || w < 0)
        {
            printf("输入的边信息不合法。\n");
            exit(1);
        }
        G->Edge[start - 1][end - 1] = w;
        G->Edge[end - 1][start - 1] = w;   // 无向图具有对称性
    }
}

/*********** 打印出邻接矩阵 *********/
void print_Matrix(MGraph G)
{
    int i, j;
    printf("\n图的顶点为: ");
    for (i = 0; i < G.vexnum; i++)
        printf("%c ", G.Vex[i]);
    printf("\n输出邻接矩阵:\n");

    // 打印表头
    printf("\t%s", " ");
    for (i = 0; i < G.vexnum; i++)
        printf("\t%c", G.Vex[i]);
    printf("\n");

    // 打印邻接矩阵
    for (i = 0; i < G.vexnum; i++)
    {
        printf("\t%c", G.Vex[i]); // 打印行标题
        for (j = 0; j < G.vexnum; j++)
        {
            if (G.Edge[i][j] == INF)
                printf("\t%s", "∞");
            else
                printf("\t%d", G.Edge[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    MGraph G;
    create_Graph(&G);
    print_Matrix(G);
    return 0;
}