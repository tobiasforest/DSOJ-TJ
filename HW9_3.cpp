#include <bits/stdc++.h>
using namespace std;
const int N = 100010;
int q[N], tmp[N];
typedef long long LL;

LL merge_sort(int q[], int l, int r)
{
    if (l >= r)
        return 0;
    int mid = l + r >> 1;
    LL res = merge_sort(q, l, mid) + merge_sort(q, mid + 1, r); // 数据个数会超出int的表示范围。
    int k = 0, i = l, j = mid + 1;
    while (i <= mid && j <= r)
        if (q[i] <= q[j])
            tmp[k++] = q[i++];
        else
        {
            res += mid - i + 1; //如果左半边的元素大于右边该数，左边元素后面的每个数也大于它，一共有mid-i+1个。
            tmp[k++] = q[j++];
        }
    while (i <= mid)
        tmp[k++] = q[i++];
    while (j <= r)
        tmp[k++] = q[j++];

    for (int i = l, j = 0; i <= r; i++, j++)
        q[i] = tmp[j];
    return res;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", &q[i]);
    while (n)
    {
        cout << merge_sort(q, 0, n - 1) << endl;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", &q[i]);
    }
    return 0;
}