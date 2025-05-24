//
// Created by 86152 on 2025/5/4.
//
#include <stdio.h>
#include <stdlib.h>

// 哈夫曼树的节点结构
typedef struct {
    int weight;  // 节点权值
    int parent, lchild, rchild;  // 父节点、左子节点、右子节点的索引
} HTNode, *HuffmanTree;

// 选择两个最小的节点，返回它们的索引
void Select(HuffmanTree HT, int end, int *s1, int *s2) {
    int min1 = INT_MAX, min2 = INT_MAX;
    for (int i = 1; i <= end; ++i) {
        if (HT[i].parent == 0) {
            if (HT[i].weight < min1) {
                min2 = min1;
                *s2 = *s1;
                min1 = HT[i].weight;
                *s1 = i;
            } else if (HT[i].weight < min2) {
                min2 = HT[i].weight;
                *s2 = i;
            }
        }
    }
}

// 构造哈夫曼树
void CreateHuffmanTree(HuffmanTree *HT, int *w, int n) {
    int m = 2 * n - 1;
    *HT = (HTNode *)malloc((m + 1) * sizeof(HTNode));
    for (int i = 1; i <= m; ++i) {
        (*HT)[i].weight = 0;
        (*HT)[i].parent = 0;
        (*HT)[i].lchild = 0;
        (*HT)[i].rchild = 0;
    }
    for (int i = 1; i <= n; ++i) {
        (*HT)[i].weight = w[i - 1];
    }
    for (int i = n + 1; i <= m; ++i) {
        (*HT)[i].weight = 0;
    }
    for (int i = n + 1; i <= m; ++i) {
        int s1, s2;
        Select(*HT, i - 1, &s1, &s2);
        (*HT)[s1].parent = i;
        (*HT)[s2].parent = i;
        (*HT)[i].lchild = s1;
        (*HT)[i].rchild = s2;
        (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
    }
}

// 打印哈夫曼树
void PrintHuffmanTree(HuffmanTree HT, int n) {
    for (int i = 1; i <= n; ++i) {
        printf("Node %d: Weight = %d, Parent = %d, Left Child = %d, Right Child = %d\n",
               i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
    }
}

int main() {
    int n = 4;  // 节点数量
    int w[] = {10, 20, 30, 40};  // 节点权值
    HuffmanTree HT;
    CreateHuffmanTree(&HT, w, n);
    printf("Huffman Tree:\n");
    PrintHuffmanTree(HT, n);
    free(HT);
    return 0;
}
/*
 结果的图形:
1.选择两个最小的节点（10和20），合并为一个新节点，权重为30。
2.选择下两个最小的节点（30和30），合并为一个新节点，权重为60。
3.选择下两个最小的节点（40和60），合并为一个新节点，权重为100。
        100
       /  \
     60    40
    /  \
   30  30
  / \
10  20
*/

