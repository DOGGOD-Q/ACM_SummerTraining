#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

inline long long read()
{
    long long num = 0, fu = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9'){if(ch == '-') fu = -1; ch = getchar();}
    while(ch >= '0' && ch <= '9'){num = (num << 3) + (num << 1) + ch - '0'; ch = getchar();}
    return num * fu;
}

struct N
{
    long long tot;
    long long lazytag;
    N(){tot = 0; lazytag = 0; }
};
N Tree[400010];
long long a[100010];
void build(int l, int r, int i)
{
    if(l == r)
    {
        Tree[i].tot = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, i << 1);
    build(mid + 1, r, (i << 1) + 1);
    Tree[i].tot = Tree[i << 1].tot + Tree[(i << 1) + 1].tot;
}

void pushDown(int i, int l, int r)
{
    Tree[i].tot += Tree[i].lazytag * (r - l + 1);
    Tree[i << 1].lazytag += Tree[i].lazytag;
    Tree[(i << 1) + 1].lazytag += Tree[i].lazytag;
    Tree[i].lazytag = 0;
}

void update(int l, int r, int l1, int r1,  int i,  long long num)
{
    if(l == l1 && r == r1)
    {
        Tree[i].lazytag += num;
        return;
    }
    pushDown(i, l, r);
    Tree[i].tot += (r1 - l1 + 1) * num;
    int mid = (l + r) >> 1;
    if(r1 <= mid)update(l, mid, l1, r1, i << 1, num);
    else if(l1 > mid)update(mid + 1, r, l1, r1, (i << 1) + 1, num);
    else
    {
        update(l, mid, l1, mid, i << 1, num);
        update(mid + 1, r, mid + 1, r1, (i << 1) + 1, num);
    }
}

void query(int l, int r, int l1, int r1, int i, long long& ans)
{
    if(l == l1 && r ==  r1)
    {
        ans += Tree[i].tot;
        ans += Tree[i].lazytag * (r - l + 1);
        return;
    }
    pushDown(i, l, r);
    int mid = (l + r) >> 1;
    if(r1 <= mid) query(l, mid, l1, r1, i << 1, ans);
    else if(l1 > mid) query(mid + 1, r, l1, r1, (i << 1) + 1, ans);
    else
    {
        query(l, mid, l1, mid, i << 1, ans);
        query(mid + 1, r, mid + 1, r1, (i << 1) + 1, ans);
    }
}

int main()
{
    int n = read(), m = read();
    for(int i=1; i<=n; i++)
    {
        a[i] = read();
    }
    build(1, n, 1);
    for(int i=1; i<=m; i++)
    {
        int flag = read();
        if(flag == 1)
        {
            int x = read(), y = read();
            long long k = read();
            update(1, n, x, y, 1, k);
        }
        else
        {
            int x = read(), y = read();
            long long ans = 0;
            query(1, n, x, y, 1, ans);
            printf("%lld\n", ans);
        }
    }
    return 0;
}