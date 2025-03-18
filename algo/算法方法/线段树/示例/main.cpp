#include <iostream>

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static const int max_num = 100; // max tree number

struct TreeNode {
    int sum;
    int max;
    int min;
};

static int g_arr[] = {0, 1, 2, 3};
static struct TreeNode tree[max_num];

static inline int left(int id)
{
    return id << 1;
}

static inline int right(int id)
{
    return (id << 1) + 1;
}

static void build(int id, int l, int r)
{
    int mid;
    if (l == r) {
        tree[id].sum = g_arr[l];
        return;
    }
    mid = (l + r) >> 1;
}

int main(int argc, char *argv[])
{
    build(1, 1, ARRAY_SIZE(g_arr));
    return 0;
}
