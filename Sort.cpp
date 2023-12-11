// 排序
// Sort

/*
1. 以下仅给出快速排序和归并排序，分别对应顺序表和链表
2. 时间复杂度均 nlog_2(n)
3. 空间复杂度快排好于归并，n ; log_2(n)
*/

// 快速排序
void quick_sort(int l, int r) // 快速排序
{
    if (l >= r)
        return;
    // 划分讲策略，划分不好导致递归层数太多，
    // 适得其反,取左右端点数据卡你就不好过，一般取中间

    int i, j, mid;

    i = l - 1;
    j = r + 1;
    mid = q[(l + r) / 2];

    while (i < j)
    {
        do
            i++;
        while (q[i] < mid);
        do
            j--;
        while (q[j] > mid);
        if (i < j)
            swap(q[i], q[j]);
    }
    quick_sort(l, j);
    quick_sort(j + 1, r);
}

// 快速排序
int w[N];                     // 辅助数组
void merge_sort(int l, int r) // 归并排序
{
    if (l >= r)
        return;

    // 先分割，再二路归并
    int mid = l + r >> 1; // 右移，相当于/2，但更快
    merge_sort(l, mid), merge_sort(mid + 1, r);

    int i = l, j = mid + 1, k = 0;

    //归并，对于归并部分的排序可以选择其他算法
    while (i <= mid && j <= r)
        if (q[i] <= q[j])
            w[k++] = q[i++];
        else
            w[k++] = q[j++];

    // 添加剩余的部分
    while (i <= mid)
        w[k++] = q[i++];
    while (j <= r)
        w[k++] = q[j++];
    // 辅助数组归并完事就要物归原主，更新原数组
    for (i = l, j = 0; j < k; i++, j++)
        q[i] = w[j];
}