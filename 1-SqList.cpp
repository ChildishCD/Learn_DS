/*
注意
1. 为指明的变量用 ElementType 类型
2. 判空、合法、越界
*/
static int Maxsize = 100010;
typedef ElementType int;

// 线性表——顺序存储
// SqList
/*================== 基础 ===================*/
/*
1. 线性表逻辑的位置是从1开始的，但实际是从数组下标0开始
   即数组的下标范围为 0~length-1
2. 每次操作要更新 L.length
*/

typedef struct {
    ElementType data[Maxsize];  // 数据
    int length;                 // 表长
} SqList;

/*
3. 初始化分为静态分配和动态分配
- 静态使用循环
- 动态使用malloc
- length 置0
*/
void InitList(SqList& L) {
    for (int i = 0; i < Maxsize; i++)
        L.data[i] = 0;
    L.length = 0;
}
void InitqList(SqList& L) {
    L.data = (int*)malloc(sizeof(int) * Maxsize);
    L.length = 0;
}

/*
4. 插入&删除
- 判空、判满
- 位置合法
- 移动元素
- 操作并更新length
*/

/*
5. 交换双指针
*/
void SwitchList(SqList& L, int i, int j) {
    ElementType temp = L.data[i];
    L.data[i] = L.data[j];
    L.data[j] = temp;
}

/*================== 题型 ===================*/

/*
1️⃣有序表插入一个元素之后依然有序
- 从后往前边移动边判断插入位置
- 判断：length=0直接插入，否则判data；插入后即可break
*/
void fun_1(SqList& L, int x) {
    for (int i = L.length; i >= 0; i--) {
        // 特判如果表空的话直接插入即可，所以要判断i是否为0
        if (x >= L.data[i - 1] || i == 0) {
            L.data[i] = x;
            L.length++;
            break;
        }
        L.data[i] = L.data[i - 1];  // 元素从后往前一点点挪动
    }
}

/*
2️⃣逆置顺序表（原地）
- 双指针，前后元素交换
- 到表中间位置，即指针相等停止
*/
void fun_2(SqList& L) {
    for (int i = 0; i < L.length / 2; i++) {
        SwitchList(L, i, L.length - 1 - i)
        // 注意L.length需要减1的原因还是因为数组下标从0开始的
    }
}

/*
3️⃣删除所有指定的元素（原地）
- 双指针，最终达到跳过所有x值来更新原数组
- i遍历，j判定不为指定的元素的数量
- 更新了length
分为无序和有序的情况
- 无序，遍历整个表
- 有序，根据实际问题选择查找算法
*/

// 无序（有序也能用）
void fun_3_1(SqList& L, int x) {
    /*省略合法性*/
    for (int i = 0, j = 0; i < L.length; i++) {
        // 如果不为指定的值，直接覆盖j的位置
        if (L.data[i] != x) {
            L.data[j] = L.data[i];
            j++;
        }
    }
    L.length = j;
}

// 有序(递增)
void fun_3_2(SqList& L, int x, int y) {
    // 先判断x和y是否合法,以及表是否为空
    if (x > y || L.len < 0)
        return;
    // 遍历线性表，分别取出x,y元素对应左右区间边界的元素下标分别交给m,n做记录
    int m, n;
    for (int i = 0; L.data[i] <= x || L.data[i] <= y; i++)
        if (L.data[i] <= x)
            m = i;
        else if (L.data[i] <= y)
            n = i;
    // 因为线性表递增有序，所以直接删除m到n的符合题意区间元素
    //(这里写得简短，但是逻辑很绕仔细品)
    for (i = n + 1; i < L.len; i++)
        L.data[i - (n - m + 1)] = L.data[i];
    // 更新线性表
    L.len -= n - m + 1;
}

/*
4️⃣设计一个算法将小于0的整数放在前部分,大于等于0的整数放在后部分
（左边和右边是两类元素）
- 双指针
- i从前往后，j从后往前，按条件交换元素直到相遇为止
*/
void fun_4(SqList& L) {
    int i = 0, j = L.len - 1;
    while (i < j) {
        while (L.data[i] < 0)
            i++;
        while (L.data[j] >= 0)
            j--;
        if (i < j)  // 防止，最后完成以后，ij越界交换
        {
            SwitchList(L, i, j)
        }
    }
}

/*
5️⃣去重 distinct
分为无序和有序的情况
- 无序: 利用哈希表，利用数组其下标为数值，存储的值表示该值是否存在
- 有序: 与无序删除类似
*/

// 无序

// 放在函数外面做全局变量，系统会自动对数组初始化为全0，哈希表来用下标做元素，空间做记录重复次数
int hash[100010];
// 注意：当然你也可以吧hash定义在函数里面，但是要写memset(hash,sizeof(hash),0)来初始化为0，因为数组在函数里面定义不会自动初始化为0
void fun_5_1(List L) {
    // 判断表是否为空or不需要去重
    if (L.len == 1 || L.len == 0)
        return;
    // 开一个非常大的数组用下标来做元素值，存在的元素存储空间放1
    for (int i = 0; i < L.len; i++)
        hash[L.data[i]] = 1;
    //
    for (int i = 0, j = 0; i < L.len; i++)
        if (hash[L.data[i]]) {
            // 当元素第一次出现的时候，就把哈希表置0，这样就达到了更新原数组去重
            hash[L.data[i]] = 0;
            L.data[j] = L.data[i];
            j++;
        }
    // 更新线性表
    L.len = j;
}

// 有序（递增）
void fun_5_1(SqList& L) {
    // 判断表是否为空or不需要去重
    if (L.len == 0 || L.len == 1)
        return;
    // 双指针算法：i为遍历原线性表，j为更新线性表
    // 注意：这里最关键的是要先对j++再更新原数组，不然会出现元素丢失
    for (int i = 0, j = 0; i < L.len; i++)
        if (L.data[i] != L.data[j]) {
            j++;
            L.data[j] = L.data[i];
        }
    // 更新线性表
    L.len = j;
}

/*
6️⃣集合操作
- 合并，交集，并集，差集
分为无序和有序的情况
- 无序用哈希，有序用双指针
*/

/*
合并 Merge
*/
void Merge(SqList& A, SqList& B, SqList& C) {
    if (A.length + B.length > C.length)  // 表长超过
        return false;
    int i = 0, j = 0, k = 0;
    while (i < A.length && j < B.length) {  // 循环，两两比较，小者存入结果表
        if (A.data[i] <= B.data[j])
            C.data[k++] = A.data[i++];
        else
            C.data[k++] = B.data[j++];
    }
    // 合并剩余的
    while (i < A.length)
        C.data[k++] = A.data[i++];
    while (j < B.length)
        C.data[k++] = B.data[j++];
    // 更新表长
    C.length = k;
}

/*
交集
*/
// 无序
int hash[100010];  // 因为无序，所以先用哈希存储
void fun_1_2(SqList& a, SqList& b, SqList& c) {
    int k = 0;
    for (int i = 0; i < a.length; i++)
        hash[a.data[i]] = 1;
    for (int i = 0; i < b.length; i++)
        if (hash[b.data[i]])  // 直接判断赋值
            c.data[k++] = b.data[i];
    c.length = k;
}
// 有序
void fun_1_1(SqList& a, SqList& b, SqList& c) {
    // 双指针算法，i指向a，j指向b，k指向c (属于归并排序里面的思想)
    int i = 0, j = 0, k = 0;
    while (i < a.length && j < b.length) {
        if (a.data[i] > b.data[j])
            j++;
        else if (a.data[i] < b.data[j])
            i++;
        else  // 若相等则更新c和所有指针
        {
            c.data[k++] = a.data[i++];
            j++;
        }
    }
    // 更新线性表c的长度
    c.length = k;
}

/*
并集
- 合并不等于并集，并集是合并后distinct的集合
*/
// 无序
//(这里的写法是保证归并之后的c，不改变ab中的相对元素位置)
int hash[100010];  // 因为无序，直接合并，然后用哈希存储去重就可以了
void fun_2_2(SqList& a, SqList& b, SqList& c) {
    // 一边合并，一边放入哈希，来防止出现重复
    int i = 0, j = 0, k = 0;
    while (i < a.length && j < b.length) {
        if (!hash[a.data[i]])  // 判断是否重复出现过，防止重复赋值给c
        {
            c.data[k++] = a.data[i++];
            hash[a.data[i]] = 1;
        }
        if (!hash[b.data[j]])  // 判断是否重复出现过，防止重复赋值给c
        {
            c.data[k++] = b.data[j++];
            hash[b.data[i]] = 1;
        }
        // 更新哈希
    }
    // 把剩下的元素放入c
    while (i < a.length)
        if (!hash[a.data[i]])
            c.data[k++] = a.data[i++];
    while (j < b.length)
        if (!hash[b.data[i]])
            c.data[k++] = b.data[j++];
    // 更新线性表c的长度
    c.length = k;
}
// 有序
void fun_2_1(SqList& a, SqList& b, SqList& c) {
    // 两个有序表，归并成一个有序表 （默认升序）
    int i = 0, j = 0, k = 0;
    while (i < a.length && j < b.length)
        if (a.data[i] < b.data[j]) {
            c.data[k++] = a.data[i++];
            c.data[k++] = b.data[j++];
        } else if (a.data[i] > b.data[j]) {
            c.data[k++] = b.data[i++];
            c.data[k++] = a.data[j++];
        } else  // 相等的话，只需要放一个
        {
            c.data[k++] = a.data[i++];
            j++:
        }
    // 把剩下的元素放入c
    while (i < a.length)
        c.data[k++] = a.data[i++];
    while (j < b.length)
        c.data[k++] = b.data[j++];
    // 更新线性表c的长度
    c.length = k;
}

/*
差集
（以下为AUB-AB，A-B同理）
*/
// 无序
int hashA[100010];  // 因为无序，所以先用哈希存储
int hashB[100010];
void fun_3_2(SqList& a, SqList& b, SqList& c) {
    // 把A和B分别放到两个哈希里面
    for (int i = 0; i < a.length; i++)
        hashA[a.data[i]] = 1;
    for (int i = 0; i < a.length; i++)
        hashB[a.data[i]] = 1;

    int i = 0, j = 0, k = 0;
    while (i < a.length && j < b.length)
        // 因为只要差值，所以只需判断两者都不相同的情况
        if (a.data[i] != b.data[j]) {
            // 判断
            if (!hashB[a.data[i]])  // 判断是否重复出现过，防止重复赋值给c
            {
                c.data[k++] = a.data[i++];
                hash[a.data[i]] = 1;
            }
            if (!hashA[b.data[j]])  // 判断是否重复出现过，防止重复赋值给c
            {
                c.data[k++] = b.data[j++];
                hash[b.data[i]] = 1;
            }
            // 更新哈希
        }
    // 把剩下的元素放入c
    while (i < a.length)
        if (!hashB[a.data[i]])
            c.data[k++] = a.data[i++];
    while (j < b.length)
        if (!hashA[b.data[i]])
            c.data[k++] = b.data[j++];
    c.length = k;
}
// 有序
void fun_3_1(SqList& a, SqList& b, SqList& c) {
    // 双指针算法，这里要差集，所以谁小先添加谁，相等就跳过
    int i = 0, j = 0, k = 0;
    while (i < a.length && j < b.length)
        if (a.data[i] < b.data[j])
            c.data[k++] = a.data[i++];
        else if (a.data[i] > b.data[j])
            c.data[k++] = b.data[j++];
        else  // 相等跳过
        {
            i++;
            j++;
        }
    // 把剩下的元素放入c
    while (i < a.length)
        c.data[k++] = a.data[i++];
    while (j < b.length)
        c.data[k++] = b.data[j++];
    // 更新线性表c的长度
    c.length = k;
}