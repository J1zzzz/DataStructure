# DataStructure
Data Structures And Algorithms ,All base structure in this course.
---

# 二叉搜索树（BST）实现

## 项目简介

这是一个用 C 语言实现的二叉搜索树（BST）程序。它支持以下功能：
- 插入节点
- 先序遍历（Pre-order Traversal）
- 中序遍历（In-order Traversal）
- 后序遍历（Post-order Traversal）
- 层序遍历（Level-order Traversal）
- 释放树内存

## 文件结构

- **`bst.c`**：包含所有实现代码。
- **`README.md`**：项目说明文档。

## 数据结构

### TreeNode

二叉搜索树的节点结构，包含：
- `int data`：节点存储的数据。
- `TreeNode *left`：指向左子节点的指针。
- `TreeNode *right`：指向右子节点的指针。

```c
typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} TreeNode;
```

### Queue

用于层序遍历的队列结构，包含：
- `QueNode *front`：队列头部指针。
- `QueNode *rear`：队列尾部指针。

```c
typedef struct QueNode {
    TreeNode *node;
    struct QueNode *next;
} QueNode;

typedef struct {
    QueNode *front;
    QueNode *rear;
} Queue;
```

## 主要功能

### 创建节点

```c
TreeNode *CreateNode(int data);
```

### 插入节点

```c
TreeNode *InsertIntoBSTree(TreeNode *root, int data);
```

### 遍历方法

- **先序遍历**：`previousTraversal(TreeNode *root)`
- **中序遍历**：`middleTraversal(TreeNode *root)`
- **后序遍历**：`lastTraversal(TreeNode *root)`
- **层序遍历**：`levelTraversal(TreeNode *root)`

### 初始化数据

```c
TreeNode *initializeData(TreeNode *root);
```

### 打印树

```c
void printTree(TreeNode *root);
```

### 释放树内存

```c
void freeTree(TreeNode *node);
```

## 如何运行

1. **编译代码**：
   使用以下命令编译代码：
   ```bash
   gcc bst.c -o bst
   ```

2. **运行程序**：
   运行编译后的程序：
   ```bash
   ./bst
   ```

3. **查看输出**：
   程序将输出以下内容：
   ```
   先序遍历:->10->5->20->15->30->25
   中序遍历:->5->10->15->20->25->30
   后序遍历:->5->15->25->30->20->10
   层序遍历:->10->5->20->15->30->25
   ```

## 示例代码

以下是主函数的代码示例：

```c
int main() {
    TreeNode *root = NULL;
    root = initializeData(root);
    printTree(root);
    freeTree(root);
    return 0;
}
```

## 注意事项

- 确保在使用完树后调用 `freeTree` 函数释放内存，避免内存泄漏。
- 如果需要插入更多数据，可以在 `initializeData` 函数中添加更多 `InsertIntoBSTree` 调用。



---

# 单链表操作实现

## 项目简介

这是一个用 C 语言实现的单链表操作程序。它支持以下功能：
- 创建带有头节点的链表
- 尾插法插入节点
- 头插法插入节点
- 判断链表是否为空
- 遍历链表
- 按位置删除节点
- 按值删除所有匹配的节点
- 销毁链表

## 文件结构

- **`linked_list.c`**：包含所有实现代码。
- **`README.md`**：项目说明文档。

## 数据结构

### Node

链表的节点结构，包含：
- `int data`：节点存储的数据。
- `Node *next`：指向下一个节点的指针。

```c
typedef struct Node {
    int data;
    struct Node *next;
} Node, *SqList;
```

## 主要功能

### 创建链表

```c
void Initialize(SqList *L);
```

### 插入节点

- **尾插法**：`void InsertTail(SqList *L, ElementType data);`
- **头插法**：`void InsertHead(SqList *L, ElementType data);`

### 判断链表是否为空

```c
bool IsEmpty(SqList *L);
```

### 遍历链表

```c
void Traverse(SqList L);
```

### 按位置删除节点

```c
void OutFromSqlistByPosition(SqList *L, int position);
```

### 按值删除所有匹配的节点

```c
int OutFromSqlistByValue(SqList *L, ElementType data);
```

### 销毁链表

```c
void DestroyList(SqList *L);
```

### 测试链表操作

```c
void TestSqList(SqList *L);
```

## 如何运行

1. **编译代码**：
   使用以下命令编译代码：
   ```bash
   gcc linked_list.c -o linked_list
   ```

2. **运行程序**：
   运行编译后的程序：
   ```bash
   ./linked_list
   ```

3. **查看输出**：
   程序将输出以下内容：
   ```
   按位置删除节点: 2
   按值删除节点: 链表中此值的个数是0
   遍历: 2
   ```

## 示例代码

以下是主函数的代码示例：

```c
int main() {
    SqList L = NULL;
    Initialize(&L);
    TestSqList(&L);
    DestroyList(&L);
    return 0;
}
```

## 注意事项

- 确保在使用完链表后调用 `DestroyList` 函数释放内存，避免内存泄漏。
- 如果需要插入更多数据，可以在 `Initialize` 函数中添加更多 `InsertHead` 或 `InsertTail` 调用。


---

# 线索二叉树实现

## 项目简介

这是一个用 C 语言实现的线索二叉树程序。它支持以下功能：
- 创建二叉树（通过前序输入）
- 中序线索化
- 中序遍历线索二叉树

## 文件结构

- **`threaded_binary_tree.c`**：包含所有实现代码。
- **`README.md`**：项目说明文档。

## 数据结构

### BiThrNode

线索二叉树的节点结构，包含：
- `TElemType data`：节点存储的数据。
- `BiThrNode *lchild`：指向左孩子或前驱的指针。
- `BiThrNode *rchild`：指向右孩子或后继的指针。
- `PointerTag Ltag`：左指针的标志。
- `PointerTag Rtag`：右指针的标志。

```c
typedef struct BiThrNode {
    TElemType data; // 结点数据
    struct BiThrNode* lchild, * rchild; // 左右孩子指针
    PointerTag Ltag, Rtag; // 左右指针的标志
} BiThrNode, *BiThrTree;
```

## 主要功能

### 创建二叉树

```c
void CreateTree(BiThrTree* tree);
```

### 中序线索化

```c
void InThreading(BiThrTree p);
```

### 中序遍历线索二叉树

```c
void InOrderThraverse_Thr(BiThrTree p);
```

## 如何运行

1. **编译代码**：
   使用以下命令编译代码：
   ```bash
   gcc threaded_binary_tree.c -o threaded_binary_tree
   ```

2. **运行程序**：
   运行编译后的程序：
   ```bash
   ./threaded_binary_tree
   ```

3. **输入测试数据**：
   程序将提示你输入前序二叉树（用 `#` 表示空结点）。例如：
   ```
   输入前序二叉树（用'#'表示空结点）:
   1 2 4 # # 5 # # 3 6 # # 7 # #
   ```

4. **查看输出**：
   程序将输出中序遍历的结果：
   ```
   输出中序序列:
   4 2 5 1 6 3 7
   ```

## 测试数据

以下是一些测试数据示例：

### 完全二叉树
```
输入前序二叉树（用'#'表示空结点）:
1 2 4 # # 5 # # 3 6 # # 7 # #
输出中序序列:
4 2 5 1 6 3 7
```

### 只有左子树的二叉树
```
输入前序二叉树（用'#'表示空结点）:
1 2 4 # # 5 # # #
输出中序序列:
4 2 5 1
```

### 只有右子树的二叉树
```
输入前序二叉树（用'#'表示空结点）:
1 # 2 # 3 # 4 # #
输出中序序列:
1 2 3 4
```

### 包含重复值的二叉树
```
输入前序二叉树（用'#'表示空结点）:
1 1 2 # # 3 # # 1 4 # # 5 # #
输出中序序列:
2 1 4 1 3 5 1
```

## 注意事项

- 确保输入的二叉树结构正确，空结点用 `#` 表示。
- 如果需要测试更多数据，可以在 `main` 函数中添加更多测试用例。


---

# 指针操作示例

## 项目简介

这是一个用 C 语言编写的示例程序，用于展示指针和指针的指针（二层指针）的使用。程序中包含三个函数，分别用于：
- 修改指针指向的值。
- 尝试修改指针本身的值。
- 修改指针指向的值（通过二层指针）。

## 文件结构

- **`pointer_example.c`**：包含所有实现代码。
- **`README.md`**：项目说明文档。

## 数据结构

### 主要函数

- **`changeValue`**：通过二层指针修改指针指向的值。
- **`changeValue2`**：尝试通过一层指针修改指针本身的值（但实际不会生效）。
- **`changePointer`**：通过一层指针修改指针指向的值。

## 主要功能

### 修改指针指向的值

```c
void changeValue(int **p) {
    *p = (int *)malloc(sizeof(int));
    **p = 111;
}
```

### 尝试修改指针本身的值

```c
void changeValue2(int *p) {
    p = (int *)malloc(sizeof(int));
}
```

### 修改指针指向的值（通过一层指针）

```c
void changePointer(int *p) {
    *p = 111;
}
```

## 如何运行

1. **编译代码**：
   使用以下命令编译代码：
   ```bash
   gcc pointer_example.c -o pointer_example
   ```

2. **运行程序**：
   运行编译后的程序：
   ```bash
   ./pointer_example
   ```

3. **查看输出**：
   程序将输出以下内容：
   ```
   地址1
   地址2
   111
   111
   ```

## 代码解释

### `changeValue` 函数

通过二层指针修改指针指向的值。`*p` 是指针的副本，`**p` 是指针指向的值。

```c
void changeValue(int **p) {
    *p = (int *)malloc(sizeof(int)); // 为指针分配内存
    **p = 111; // 修改指针指向的值
}
```

### `changeValue2` 函数

尝试通过一层指针修改指针本身的值，但实际上修改的是指针的副本，不会影响原始指针。

```c
void changeValue2(int *p) {
    p = (int *)malloc(sizeof(int)); // 修改指针的副本
}
```

### `changePointer` 函数

通过一层指针修改指针指向的值。`*p` 是指针指向的值。

```c
void changePointer(int *p) {
    *p = 111; // 修改指针指向的值
}
```

## 注意事项

- 在 `changeValue` 函数中，通过二层指针可以成功修改指针指向的值。
- 在 `changeValue2` 函数中，尝试修改指针本身的值，但由于传递的是指针的副本，因此不会影响原始指针。
- 在 `changePointer` 函数中，通过一层指针可以成功修改指针指向的值。




# 链栈的实现

## 代码

### 数据结构
```c
typedef int ElementType;
typedef struct node {
    ElementType data;
    struct node *next;
} StackNode;

typedef struct stack {
    StackNode *top;
} Stack;
```

### 函数声明
```c
void InitStack(Stack *s);
bool IsEmptyStack(Stack *s);
void DestroyStack(Stack *s);
void PushStack(Stack *s, ElementType data_element);
void PopStack(Stack *s);
void DisplayStack(Stack *s);
```

### 主函数
```c
int main() {
    Stack s;
    InitStack(&s);
    PushStack(&s, 1);
    PushStack(&s, 2);
    PopStack(&s);
    DisplayStack(&s);
    DestroyStack(&s);
    return 0;
}
```

### 重要代码片段

#### 初始化栈
```c
void InitStack(Stack *s) {
    s->top = NULL;
}
```

#### 判断栈是否为空
```c
bool IsEmptyStack(Stack *s) {
    return s->top == NULL;
}
```

#### 进栈操作
```c
void PushStack(Stack *s, ElementType data_element) {
    StackNode *p = (StackNode *)malloc(sizeof(StackNode));
    p->data = data_element;
    p->next = s->top;
    s->top = p;
}
```

#### 出栈操作
```c
void PopStack(Stack *s) {
    if (IsEmptyStack(s)) {
        printf("Stack is empty\n");
        return;
    }
    StackNode *p = s->top;
    printf("Element in the stack on the top: %d\n", p->data);
    s->top = p->next;
    free(p);
}
```

#### 显示栈内容
```c
void DisplayStack(Stack *s) {
    if (IsEmptyStack(s)) {
        printf("Stack is empty\n");
        return;
    }
    StackNode *p = s->top;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
```

#### 销毁栈
```c
void DestroyStack(Stack *s) {
    while (s->top != NULL) {
        StackNode *p = s->top;
        s->top = s->top->next;
        free(p);
    }
}
```

## 示例输出
```
Element in the stack on the top: 2
1 
```

## 代码说明
- **`InitStack`**：初始化链栈，将栈顶指针设置为`NULL`。
- **`IsEmptyStack`**：判断链栈是否为空。
- **`PushStack`**：将一个新元素压入栈顶。
- **`PopStack`**：弹出栈顶元素并输出其值。
- **`DisplayStack`**：按栈顶顺序输出链栈中的所有元素。
- **`DestroyStack`**：释放链栈占用的内存。

## 注意事项
- 在程序结束时，建议调用`DestroyStack`函数释放链栈占用的内存，避免内存泄漏。
```


## 作者

Jzzzz

---

希望这个 `README.md` 文档能帮助你更好地组织和说明你的代码！如果有任何需要修改或补充的地方，请随时告诉我。