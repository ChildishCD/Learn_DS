// 栈
// Stack
/*
1. 分为顺序存储和链式存储，实现和顺序表相似
2. 重要操作：Pop(),Push(),GetTop(),isEmpty(),isFull()
*/

// 顺序
typedef struct
{
    // int *data;//动态建栈的过程，如果这样写的话,下面 initStack要用第一种方式
    int data[MaxSize]; // 静态方式常用，直接定义数组长度，初试化过程就超级简单
    int top;
} SeqStack, *LinkStack;

// 动态初始化，适合结构体里面定义的是 int *data;
void initStack(LinkStack &s)
{
    s = (SeqStack *)malloc(sizeof(SeqStack));
    s->data = (int *)malloc(sizeof(int) * MaxSize);
    s->top = -1;
}

// 链式
typedef struct LinkNode
{
    int data;
    struct LinkNode *next;
} LinkNode, *LinkStack;

// 建栈，初始化
void initStack(LinkStack &s)
{
    s = (LinkStack)malloc(sizeof(LinkNode));
    s->next = NULL;
}

// 静态初始化（常用）
void initStack(LinkStack &s)
{
    s->top = -1;
}

/*=====================================================*/

// 队列
// Queue
/*
1. 分为顺序存储和链式存储，实现和顺序表相似
2. 分为循环和非循环，结构一样，只是以下操作的判断不同
2. 重要操作：DeQueue(),EnQueue(),isEmpty(),isFull()
*/

// 顺序
typedef struct
{
    int data[MaxSize];
    int front, rear;
} Queue, *PQueue;

void initQueue(Queue &Q)
{
    Q.front = Q.rear = 0;
}

// 链式
typedef struct qNode
{
    int data;
    struct qNode *next;
} qNode, *queue;

typedef struct
{
    queue front;
    queue rear;
} Queue;

void initQueue(Queue &Q)
{
    Q.front = Q.rear = (queue)malloc(sizeof(qNode));
    Q.front->next = NULL;
}

/*================== 题型 ===================*/

/*
1️⃣回文数
- 将字符串前一半入栈，然后，栈中元素和字符串后一半比较。
*/
int isPalindrome(char *t)
{
    InitStack(S);
    int len = strlen(t);              // 求字符串长度
    for (int i = 0; i < len / 2; i++) // 将一半字符入串
        Push(S, t[i]);
    if (len % 2 != 0)
        i++;               // 长度为奇数，跳过中间字段
    while (!EmptyStack(S)) // 每弹出一个字符与相应字符比较
    {
        int tmp = Pop(S);
        if (tmp != t[i])
            return 0; // 不相等返回 0
        else
            i++
    }
    return 1; // 比较完毕均相等返回 1
}

/*
2️⃣括号匹配
*/
bool Match(char exp[], int n)
{
    int i = 0;
    char e;
    bool match = true;
    LinkStNode *st;
    InitStack(st); // 初始化栈
    while (i < n && match)
    {
        if (exp[i] == '(') // 当前字符为左括号，将其进栈24
            Push(st, exp[i]);
        else if (exp[i] == ')') // 当前字符为右括号
        {
            if (GetTop(st, e) == true) // 成功取栈顶元素 e
            {
                if (e != '(')      // 栈顶元素不为 （ 时
                    match = false; // 表示不匹配
                else               // 栈顶元素为 ）时
                    Pop(st, e);    // 将栈顶元素出栈
            }
            else
                match = false; // 无法取栈顶元素时表示不匹配
        }
        i++; // 继续处理其他字符
    }
    if (!StackEmpty(st)) // 栈不空时，表示不匹配
        match = false;
    DestroyStakck(st);
    return match;
}
