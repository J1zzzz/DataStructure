# 无向图邻接矩阵表示程序

## 程序简介

本程序使用 C 语言实现了一个无向图的创建和邻接矩阵的打印功能。它通过压缩存储的方式存储邻接矩阵，节省了存储空间，适用于稀疏图的存储。

## 功能概述

1. **创建无向图**：用户可以输入无向图的顶点数和边数，并依次输入每个顶点的信息以及每条边的起点序号、终点序号和权值，从而创建一个无向图。
2. **打印邻接矩阵**：程序会以美观的格式打印出创建的无向图的邻接矩阵，方便用户查看图的结构。

## 编译与运行

### 编译

确保你的系统已安装 C 语言编译器（如 GCC）。在终端中进入程序所在的目录，运行以下命令进行编译：

```bash
gcc -o graph graph.c
```

### 运行

编译完成后，运行生成的可执行文件：

```bash
./graph
```

## 使用示例

### 输入示例

```
请输入所创建无向图的顶点数和边数(用空格隔开): 4 4
请输入第 1 个顶点的信息: A
请输入第 2 个顶点的信息: B
请输入第 3 个顶点的信息: C
请输入第 4 个顶点的信息: D

请输入边的起点序号，终点序号，权值(用空格隔开): 1 2 5
请输入边的起点序号，终点序号，权值(用空格隔开): 1 3 3
请输入边的起点序号，终点序号，权值(用空格隔开): 2 4 2
请输入边的起点序号，终点序号，权值(用空格隔开): 3 4 1
```

### 输出示例

```
图的顶点为: A B C D 
输出邻接矩阵:

		A		B		C		D
	A	0	    5	    3	    ∞
	B	5	    0	    ∞	    2
	C	3	    ∞	    0	    1
	D	∞	    2	    1	    0
```

## 代码结构说明

### 数据结构

- **`MGraph` 结构体**：用于存储无向图的信息。
    - `VertexType Vex[MaxVertexNum]`：顶点表，存储图的顶点信息。
    - `EdgeType Edge[(MaxVertexNum * (MaxVertexNum - 1)) / 2]`：压缩存储的邻接矩阵，只存储下三角矩阵（包括对角线），节省存储空间。
    - `int vexnum, edgenum`：图的顶点数和边数。
    - `int adjIndex[MaxVertexNum + 1]`：压缩矩阵索引，用于快速定位每一行的起始位置。

### 函数功能

- **`create_Graph`**：创建无向图。
    - 用户输入图的顶点数和边数。
    - 依次输入每个顶点的信息。
    - 输入每条边的起点序号、终点序号和权值。
    - 确保输入的边信息合法，并将边的信息存储到压缩邻接矩阵中。

- **`print_Matrix`**：打印邻接矩阵。
    - 以美观的格式打印出无向图的邻接矩阵。
    - 利用 `adjIndex` 数组快速定位压缩矩阵中的元素。

## 注意事项

1. **输入合法性**：
    - 输入的顶点数和边数必须合法，顶点数应大于 0，边数应大于等于 0。
    - 输入的边信息也必须合法，起点序号和终点序号应在顶点范围内，权值应大于等于 0。
    - 输入的边的起点序号和终点序号应满足 \(1 \leq \text{start}, \text{end} \leq \text{vexnum}\)。
    - 输入的权值应小于 `INF`，以免与无穷大混淆。

2. **存储方式**：
    - 邻接矩阵的存储采用压缩存储方式，只存储下三角矩阵，节省了存储空间。
    - 利用一维数组存储边，如果(i<j),即下三角,如果(j<i),即上三角。
    - 为了便于查找上三角的内容，还设置了另一一维数组，该数组是为了设置每一行首元素的edge数组的下标。
    - 对于无向图中的每条边，只存储一次权值，且存储在下三角矩阵中。

3. **程序限制**：
    - 顶点数目最大值为 `MaxVertexNum`，默认为 100。
    - 权值的最大值为 `INF`，默认为 32767。

## 示例代码

以下是程序的核心代码片段，展示了如何创建无向图和打印邻接矩阵：

```c
/********** 创建无向图 ********/
void create_Graph(MGraph *G) {
    int i, j, k = 0;
    int start, end;  // 边的起点序号、终点序号
    int w;           // 边上的权值
    printf("请输入所创建无向图的顶点数和边数(用空格隔开): ");
    if (scanf("%d %d", &G->vexnum, &G->edgenum) != 2 || G->vexnum <= 0 || G->edgenum < 0) {
        printf("输入的顶点数或边数不合法。\n");
        exit(1);
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
```