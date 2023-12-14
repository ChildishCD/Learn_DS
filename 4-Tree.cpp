#define MAXSIZE 12
typedef ElementType int;

// 二叉树
// Tree

/*================== 基础 ===================*/
/*
1. 四种遍历，分为递归和非递归，以下只写递归
*/
typedef struct Node {
    char data;
    struct node* left;
    struct node* right;
} Node, *Tree;

void Visit(Tree root) {
    printf(" %c - ", root->data);
}

// 前序 pre
void preOrder(Tree root) {
    if (root != NULL) {
        Visit(root);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// 中序 in
void inOrder(Tree root) {
    if (root != NULL) {
        inOrder(root->left);
        Visit(root);
        inOrder(root->right);
    }
}

// 后序 post
void postOrder(Tree root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        Visit(root);
    }
}

// 层次遍历 level
void levelOder(Tree root) {
    if (root == NULL)
        return;
    Queue q;
    InitQueue(q);
    Tree node;
    EnQueue(q, node);

    while (!isEmpty(q)) {
        DeQueue(Q, node);
        Visit(node);
        if (node->left != NULL)
            EnQueue(q, node->left);
        if (node->right != NULL)
            EnQueue(q, node->right);
    }
}

/*================== 题型 ===================*/

/*
1️⃣树的高度
- 利用前序遍历，全局变量存储高度
- 利用后续遍历，每一次递归+1
重要思想
- 前序遍历 自顶向下 传递参数
- 后续遍历 自底向上 返回参数
*/
int height = 0;
void preOrder(Tree root, int n) {
    if (root != NULL) {
        // n的初始值为0，即 preOrder(T,0);
        if (root == NULL)
            return;
        if (n > height)
            height = n;

        preOrder(root->left, n + 1);
        preOrder(root->right, n + 1);
    }
}

int treeHeight(Tree root) {
    if (root == NULL)
        return 0;
    int left = treeHeight(root->left);
    int right = treeHeight(root->right);
    return left > right ? left + 1 : right + 1;
}

/*
2️⃣树的宽度
*/
// 求数组的最大值
int maxArray(int array[], int len) {
    /*省略判空返回特殊值*/
    int aMax = array[0];
    for (int i = 0; i < len; i++) {
        if (array[i] > aMax)
            aMax = array[i];
    }
    return aMax;
}

// 保存每一层的节点数目
int width[height];
// 用先序遍历统计每层的节点数
//  调用 levelCount(T, 0)
void levelCount(Tree root, int level) {
    if (root == NULL)
        return;
    width[level]++;  // 遍历了一个节点
    levelCount(root->left, ++level);
    levelCount(root->right, ++level);
}

int treeWidth(Tree T) {
    /*省略数组初始化*/
    levelCount(T, 0);
    return maxArray(width, height);
}

/*
3️⃣树的带权路径长度
*/
int WPL = 0;
void calWPL(Tree T, int level) {
    if (T == NULL)
        return;
    if (T->left == NULL && T->right == NULL) {
        WPL += level * T->wight;
    }
    calWPL(root->left, ++level);
    calWPL(root->right, ++level);
}

int WPL(Tree T) {
    calWPL(T, 0);
    int result = WPL;
    WPL = 0;
    return result;
}

int WPL(BTree* root)  // 根据WPL的定义采用递归算法实现
{
    if (root == NULL)
        return -1;
    return WPLl(root, 0);
}
int WPLl(BTree* root, int d)  // d为结点深度
{
    if (root->left == NULL && root->right == NULL)
        return (root->weight * d);
    else
        return (WPLl(root->left, d + 1) + WPLl(root->right, d + 1));
}

/*
4️⃣判断是否为二叉排序树
- 错误的做法，用遍历判断左<中<右
- 正确：利用中序遍历，判断遍历序列是否有序，边遍历边判断
*/
int temp = MIN_INT;  // 设为定义域的最小值(升序)，MIN_INT为int的最小值
bool flag = ture;
void inBST(Tree T) {
    if (flag) {
        if (T == NULL)
            return;
        inOder(T->left);
        if (T->data >= temp)
            temp = T->data;
        else
            flag = false;
        inOder(T->right);
    }
}

bool isBST(Tree root) {
    inBST(root);
    bool result = flag;
    /*省略初始化全局变量*/
    return result;
}

/*
5️⃣判断平衡
*/
bool flag = ture;
// 利用后序遍历
int inBalance(Tree root) {
    if (root == NULL || !flag)
        return 0;
    int left = inBalance(root->left);
    int right = inBalance(root->right);
    int temp = left - right;
    if (temp > 1 || temp < -1)
        flag = false;
    return left > right ? left + 1 : right + 1;
}

bool isBalance(Tree T) {
    inBalance(T);
    return flag;
}

/*
6️⃣判断完全二叉树
- 利用层序遍历
- 遇到第一个孩子不满的节点，且只可能是只有叶子节点和只有左孩子的节点
- 后边的节点都是叶子节点
*/
bool isComp = true;
bool flag = false;  // 表示此时遍历的节点都是叶子节点
void inComplete(Node* p) {
    if (!isComp)
        return;
    // 无孩子
    if (p->left == NULL && p->right == NULL)
        flag == true;
    // 只有右孩子
    if (p->left == NULL && p->right != NULL)
        isComp == false;
    // 只有左孩子
    if (p->left != NULL && p->right == NULL) {
        if (flag)
            isComp = false;
        flag = false;
    }
    // 有左右孩子
    if (p->left != NULL && p->right != NULL) {
        if (flag)
            isComp = false;
    }
}

bool isComlete(Tree root) {
    if (root == NULL)
        return;
    Queue q;
    InitQueue(q);
    Tree node;
    EnQueue(q, node);

    while (!isEmpty(q)) {
        DeQueue(Q, node);

        inComplete(node);
        // 添加终止条件
        if (!isComp)
            return false;
        if (node->left != NULL)
            EnQueue(q, node->left);
        if (node->right != NULL)
            EnQueue(q, node->right);
    }
    return true;
}