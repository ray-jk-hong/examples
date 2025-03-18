#include <iostream>

// 区间查询：树状数组可以快速计算数组区间的合
// 单点修改：可以做单点的修改

using namespace std;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
static int V[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static int tree[100];

#define lowbit(x) ((x) & (-x))

static int query(int n)
{
    int ans = 0;
    for (int pos = n; pos > 0; pos -= lowbit(pos)) {
        ans += tree[pos];
    }
    return ans;
}

static void update(int i, int x)
{
    for (int pos = i; pos < ARRAY_SIZE(V); pos += lowbit(pos)) {
        tree[pos] += x;
    }
}

static int query_range(int s, int e)
{
    return query(e) - query(s);
}

static void init(void)
{
    for (int i = 1; i <= ARRAY_SIZE(V); i++) {
        update(i, V[i]);
    }
}

int main(int argc, char *argv[])
{
    int ans;
    // 1. tree要更新上去
    init();
    ans = query(3);
    cout << "ans=" << ans << endl;
    return 0;
}
