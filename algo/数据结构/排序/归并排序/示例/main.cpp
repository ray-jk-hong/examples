#include <iostream>

static int res[1000];

static void merge(int ar[], int l, int m, int r)
{
}

static void _merge_sort(int ar[], int l, int r)
{
    if (l < r) {
        int m = (l + r) >> 1;
        _merge_sort(ar, l, m);
        _merge_sort(ar, m + 1, r);
        merge(ar, l, m, r);
    }

}

static void merge_sort(int ar[], int len)
{
    _merge_sort(ar, 1, len);
}

int main(int argc, char *argv[])
{
    return 0;
}