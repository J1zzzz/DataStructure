//
// Created by 86152 on 2025/5/8.
//
#include <stdio.h>
#include <stdlib.h>

#define MAXN 105  // 最大元素数量

int parent[MAXN];  // 存储每个元素的“父亲”节点
int rank[MAXN];    // 存储每个元素所在树的高度（用于按秩合并）

// 初始化并查集
void init(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;  // 初始时每个元素的“父亲”是它自己
        rank[i] = 0;    // 初始时树的高度为0
    }
}

// 查找操作（带路径压缩）
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // 路径压缩
    }
    return parent[x];
}

// 合并操作（按秩合并）
void union_sets(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) {  // 如果两个元素不在同一个集合中
        if (rank[root_x] < rank[root_y]) {
            parent[root_x] = root_y;  // 将较小的树接到较大的树上
        } else if (rank[root_x] > rank[root_y]) {
            parent[root_y] = root_x;
        } else {
            parent[root_y] = root_x;
            rank[root_x]++;  // 如果两棵树高度相同，合并后高度加1
        }
    }
}

int main() {
    int n, m;  // n为元素数量，m为操作数量
    scanf("%d %d", &n, &m);

    init(n);  // 初始化并查集

    for (int i = 0; i < m; i++) {
        int op, x, y;
        scanf("%d %d %d", &op, &x, &y);
        if (op == 0) {  // 合并操作
            union_sets(x, y);
        } else if (op == 1) {  // 查询操作
            if (find(x) == find(y)) {
                printf("Yes\n");  // x和y在同一个集合中
            } else {
                printf("No\n");
            }
        }
    }

    return 0;
}