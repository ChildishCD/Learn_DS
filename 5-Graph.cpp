// 图
// Graph
/*================== 基础 ===================*/
/*
1. 分为邻接矩阵和邻接表存储的方法
*/
#define MaxV 10
// 邻接矩阵
typedef struct {
    char Vex[MaxV];         // 顶点表
    int Edges[MaxV][MaxV];  // 邻接矩阵/边表
    int v_num;              // 顶点的数目
    int e_num;              // 边的数目
} MGraph;

// 邻接表
// 边表结点
typedef struct node {
    int adjvex;         // 邻接点域
    struct node* next;  // 指向下一个邻接点的指针域
} Edgenode;

// 表头（顶点）结点
typedef struct vnode {
    int vertex;      // 顶点域
    Edgenode* link;  // 边表头指针
} Vexnode;

// adjlist是邻接表类型
typedef Vexnode adjlist[MaxV];  // 表头结点类型的顺序存储方式

typedef struct {
    adjlist adjlist;  // 邻接表
    int v_num;        // 顶点的数目
    int e_num;        // 边的数目
} Adjgraph;           // Adjgraph是以邻接表方式存储的图类型