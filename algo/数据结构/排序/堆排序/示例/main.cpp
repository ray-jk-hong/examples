#include <iostream>
#include <limits.h>
#include <stdio.h>

using namespace std;

static inline int left(int id)
{
    return id * 2;
}

static inline int right(int id)
{
    return id * 2 + 1;
}

static inline void swap(int *x, int *y)
{
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}

static int get_max_id(int heap[], int len, int id)
{
    int l = left(id), r = right(id);
    int l_val = (l <= len) ? heap[l] : INT_MIN;
    int r_val = (r <= len) ? heap[r] : INT_MIN;
    int largest;

    largest = (l_val > heap[id]) ? l : id;
    largest = (r_val > heap[largest]) ? r : largest;

    return largest;
}

static void max_heapify(int heap[], int len, int id)
{
    int max_id = get_max_id(heap, len, id);     // 当前id于左右子节点中，选出最大值的id
    if (max_id != id) {                         // 如果子节点中有比当前节点大的，则进行交换并继续向下维护最大堆性质
        swap(&heap[id], &heap[max_id]);
        max_heapify(heap, len, max_id);
    }
}

static void build_max_heap(int heap[], int len)
{
    for (int i = len / 2; i > 0; i--) {     // 这里建立最大堆，是从len / 2 到1就可以了，因为len / 2 + 1到len都是叶节点，不必扫
        max_heapify(heap, len, i);
    }
}

int main(int argc, char *argv[])
{
    int g_heap[] = {0, 4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    int heap_len = 10;

    build_max_heap(g_heap, 10);             // 1. 建立一个最大堆
    for (int i = 10; i > 1; i--) {
        swap(g_heap[i], g_heap[1]);         // 2. 每次把heap的root节点，叶就是最大的节点和最末尾的节点换掉
        heap_len -= 1;                      // 3. 维护最大堆的长度减小 1， 因为最大的已经换到最后了
        max_heapify(g_heap, heap_len, 1);   // 4. 从节点1开始，重新维护最大堆性质 
    }

    for (int i = 1; i <= heap_len ; i++) {
        printf("g_heap[%d]=%d\n", i, g_heap[i]);
    }
    
    return 0;
}
