// 线性表——链式存储
// LinkList
static int Maxsize = 100010;
typedef ElementType int;

/*================== 基础 ===================*/
/*
1. 用链表来写线性表一般不用写长度length,因为链表属于动态分配存储
2. int length;如果真需要加上的话,注意更新链表的时候只更新head->lengt
3. 单链表，循环单链表，双链表，循环双链表
*/

typedef struct ListNode {
    ElementType val;  // 节点数据
    ListNode* next;   // 指向下一个节点的指针
} ListNode, *LinkList;

/*
4. 建立单链表
- 利用头插法
*/
// 建立单链表（头插法,将顺序存储->构建成链表）
void CreateList(LinkList& L, int a[], int n) {
    ListNode* s;
    int i;
    L = (ListNode*)malloc(sizeof(ListNode));
    L->next = NULL;
    for (int i = 0; i < n; i++) {
        s = (ListNode*)malloc(sizeof(ListNode));
        s->val = a[i];
        s->next = L->next;
        L->next = s;
    }
}
// 建立单链表（头插法，输入）
LinkList CreateList(LinkList& L) {
    ListNode* p = L;
    ListNode* s = NULL;
    scanf("%d", &L.len);
    for (int i = 0; i < L.len; i++) {
        s = (ListNode*)malloc(size(ListNode));
        scanf("%d", &s.val);
        s->next = p;
        L = s;
    }
    return L;
}

/*
5. 插入
- 头插法，尾插法，常规插入
*/
// 用头插法简单插入一个新结点并返回链表
LinkList CreateList_Head(LinkList head) {
    // 创建新结点
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    scanf("%d", &p->val);  // cin >> p->val;
    // 将新结点按正确逻辑从头结点后面插入
    p->next = head->next;
    head->next = p;
    //  head->length ++;

    // 其实可以不用返回链表,因为我们传进来的就是指针
    return head;
}

// 用尾插法简单插入一个新结点(只有头结点,没有尾指针的写法)
// 有尾指针的话,跟头插法的写法类似
LinkList CreateList_tail(LinkList head) {
    // 创建新结点
    ListNode* q = (ListNode*)malloc(sizeof(ListNode));
    scanf("%d", &q->val);  // cin >> q->val;
    // 用一个临时指针p来遍历找到末尾结点
    ListNode* p = head;
    // 先找到链表最后一个结点
    while (p) {
        if (p->next)
            p = p->next;
        else
            break;
    }
    // 找到之后, 将新结点按正确逻辑尾结点后面插入
    p->next = q->next;
    q->next = NULL;  // 注意，插入尾结点最后指向的是空(NULL)
    //  head->length ++;

    // 其实可以不用返回链表,因为我们传进来的就是指针
    return head;
}

// 链表中指定位置插入新元素,这里用布尔类型好区分是否插入成功
bool InsertListNode(LinkList head, int pos, int val) {
    // 判断插入位置是否合法
    if (pos > 0) {
        // 找到插入位置的前驱结点
        ListNode* pre = head;
        for (int i = 0; pre && i < pos - 1; i++)
            pre = pre->next;
        // 遍历完之后,要判断插入位置的前驱结点是否存在
        if (pre) {
            // 存在的话,就创建新结点赋e值,按逻辑插入链表中
            ListNode* p = (ListNode*)malloc(sizeof(ListNode));
            p->val = val;
            p->next = pre->next;
            pre->next = p;
            //      head->length ++;

            return true;
        }
    }
    return false;
}

/*
6. 查找&删除
*/
bool DeleteListNode(LinkList head, int e) {
    // 找到要删除结点的前驱结点
    ListNode* pre = head;
    while (pre->next && pre->next->val != e)
        pre = pre->next;
    // 找到之后, 将结点按正确逻辑删除
    if (pre->next) {
        ListNode* q = pre->next;
        pre->next = q->next;
        free(q);  // 释放要删除的结点的动态存储空间
        return true;
    }
    return false;
}

/*
7. 遍历
*/
void print(LinkList head) {
    for (ListNode* p = head->next; p; p = p->next)
        // printf("%d ",p->val);
        cout << p->val << " ";
}

/*================== 题型 ===================*/

// 双指针策略思想（重点）： ✔ 一快，一慢 ✔ 一早，一晚 ✔ 一左，一右

/*
1️⃣将两个递增的有序链表 La 和 Lb 合并为一个递增的有序链表 Lc
- 二路归并可用
*/
void MergeList(LinkList& La, LinkList& Lb, LinkList& Lc) {
    ListNode *pa, *pb, *pc;
    pa = La->next;  // pa 是链表 La 的工作指针，初始化为首元结点
    pb = Lb->next;  // pb 是链表 Lb 的工作指针，初始化为首元结点
    Lc = pc = La;   // La 的头结点作为 Lc 的头结点
    while (pa && pb) {
        if (pa->data < pb->data) {
            // 取较小者 Lb 中的元素，将 pb 链接在 pc 的后面，pb 指针后移
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }  // if
        else if (pa->data > pb->data) {
            // 取较小者 Lb 中的元素，将 pb 链接在 pc 的后面，pb 指针后移
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }  // else if
        else {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
            q = pa->next;
            free(pb);
            pb = q;
        }
    }
    pc->next = pa ? pa : pb;  // 将非空的剩余元素直接链接在 Lc 表的最好
    free(Lb);                 // 释放 Lb 的头结点
}

/*
2️⃣将两个非递减的有序表 La 和 Lb 合并为一个非递增的有序链表 Lc
- 利用头插法实现逆序
- 条件为pa || pb，需要将链表全部逆序
*/
void MergeList(LinkList& La, LinkList& Lb, LinkList& Lc) {
    ListNode *pa, *pb, *pc, *q;
    pa = La->next;  // pa 是链表的 La 的工作指针，初始化为首元结点
    pb = Lb->next;  // pb 是链表 Lb 的工作指针，初始化为首元结点
    Lc = La;
    pc = La;  // 用 La 的头结点作为 Lc 的头结点
    Lc->next = NULL;
    while (pa || pb)  // 只要有一个表未到达表尾指针，用 q 指向待摘取的元素
    {
        if (!pa)  // La 表为空，用 q 指向 pb,pb 指针后移
        {
            q = pb;
            pb = pb->next;
        } else if (!pb)  // Lb 表为空，用 q 指向 pa,pa 指针后移
        {
            q = pa;
            pa = pa->next;
        } else if (pa->data <= pb->data)
        // 取较小者 La 中的元素，用 q 指向 pa， pa 指针后移
        {
            q = pa;
            pa = pa->next;
        } else  // 取较小者 Lb 中的元素，用 q 指向 pb，pb 指针后移
        {
            q = pb;
            pb = pb->next;
        }
        q->next = Lc->next;
        Lc->next = q;
    }
    free(Lb)
}

/*
3️⃣删除某值
- 最值同理，遍历完整个链表后删除
*/
void Delete_x(
    LinkList& L,
    ElemType x) {  // L 为带头结点的单链表，本算法删除 L 中所有值为 x 的结点
    ListNode *p = L->next, *pre = L, *q;  // 置 p 和 pre 的初值
    while (p != NULL) {
        if (p->data == x) {
            q = p;  // q 指向该结点
            p = p->next;
            pre->next = p;  // 删除*q 结点
            free(q);        // 释放*q 结点的空间
        } else              // 否则，pre 和 p 同步后移
        {
            pre = p;
            p = p->next;
        }
    }
}

/*
4️⃣查找倒数第k个元素
*/
int Search_k(LinkList list, int k) {  // 查找链表上第 k 个位置上的结点
    int i = 0;                        // 初始化计数器
    ListNode *p = list->next, *q = list->next;  // p，q 均指向首元结点
    while (p != NULL)  // 扫描链表，直到 p 为空
    {
        p = p->next;  // p 移动到下一个结点
        if (i < k)
            i++;  // 计数器+1
        else
            q = q->next;  // q 移到下一个结点
    }
    if (i == k) {
        cout << q->data;  // 查找成功，输出 data 域的值
        return 1;
    } else
        return 0;  // 如果链表长度小于 k，查找失败
}

/*
5️⃣判断链表中是否有环
- 快慢指针遍历链表，快指针步距为 2，慢指针步距为 1
- 如果链表带环，两指针一定会在环中相遇。
*/
Int hasCycle(ListNode* head) {  // 判断链表是否有环
    if (head == NULL || head->next == NULL)
        return 0;
    ListNode* fast = head->next;
    ListNode* slow = head;
    while (slow != fast) {
        if (fast == NULL || fast->next == NULL)  // 链表无环
            return 0;
        slow = slow->next;        // 慢指针每次走一步
        fast = fast->next->next;  // 快指针每次走两步
    }
    return 1;
}