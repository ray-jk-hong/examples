#include <iostream>

using namespace std;

static const int n = 100;
static int fa[n];

// 并查集有以下三个操作
// 1. init: 初始化，起始就是自己是自己的father
// 2. find: 就是找到我自己group的祖先
// 3. merge: 就是合并两个group为一个group
static void init(void)
{
    for (int i = 0; i < n; i++) {
        fa[i] = i;
    }
}

static int find(int x)
{
    if (fa[x] == x) {
        return x;
    }
    return find(fa[x]);
}

static void merge(int x, int y)
{
    fa[find(x)] = find(y);
}

int main(int argc, char *argv[])
{
    init();
    return 0;
}