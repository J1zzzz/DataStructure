# 无向图邻接表表示程序

## 程序简介

本程序使用 C 语言实现了一个无向图的创建和打印功能，采用邻接表存储方式。邻接表是一种适合稀疏图的存储方式，能够有效节省存储空间，同时便于图的遍历和操作。

## 功能概述

1. **创建无向图**：用户可以输入无向图的顶点数和边数，并依次输入每个顶点的信息以及每条边的起点序号、终点序号和权值，从而创建一个无向图。
2. **打印邻接表**：程序会以美观的格式打印出创建的无向图的邻接表，方便用户查看图的结构。

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
输出邻接表:

A: B(5) -> C(3) -> NUll
B: A(5) -> D(2) -> NUll
C: A(3) -> D(1) -> NUll
D: B(2) -> C(1) -> NUll
```

## 代码结构说明

### 数据结构

- **`EdgeNode` 结构体**：用于表示邻接表中的边表节点。
    - `int adjvex`：邻接点的序号。
    - `int weight`：边的权值。
    - `EdgeNode* next`：指向下一个邻接点的指针。

- **`VertexNode` 结构体**：用于表示邻接表中的顶点表节点。
    - `VertexType data`：顶点信息。
    - `EdgeNode* firstedge`：指向第一个邻接点的指针。

- **`MGraph` 结构体**：用于存储无向图的信息。
    - `VertexNode vexs[MaxVertexNum]`：顶点表数组。
    - `int vexnum, edgenum`：图的顶点数和边数。

### 函数功能

- **`create_Graph`**：创建无向图。
    - 用户输入图的顶点数和边数。
    - 依次输入每个顶点的信息。
    - 输入每条边的起点序号、终点序号和权值。
    - 确保输入的边信息合法，并将边的信息存储到邻接表中。

- **`print_Graph`**：打印邻接表。
    - 以美观的格式打印出无向图的邻接表，展示每个顶点及其邻接点和权值。

## 注意事项

1. **输入合法性**：
    - 输入的顶点数和边数必须合法，顶点数应大于 0，边数应大于等于 0。
    - 输入的边信息也必须合法，起点序号和终点序号应在顶点范围内，权值应大于等于 0。
    - 输入的边的起点序号和终点序号应满足 \(1 \leq \text{start}, \text{end} \leq \text{vexnum}\)。
    - 输入的权值应小于 `INF`，以免与无穷大混淆。

2. **存储方式**：
    - 邻接表存储方式通过顶点表和边表来表示图，每个顶点对应一个链表，链表中的节点表示与该顶点相邻的顶点及其边的权值。

3. **程序限制**：
    - 顶点数目最大值为 `MaxVertexNum`，默认为 100。
    - 权值的最大值为 `INF`，默认为 32767。

## 示例代码

以下是基于邻接表存储的结构体代码：

```c
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
```

以下是邻接表存储无向图代码：
```c
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
```
以下是打印邻接表:
```
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
        printf("\n");
    }
}
```
