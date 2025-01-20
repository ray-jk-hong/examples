#include <stdio.h>

typedef unsigned int u32;
// 定义结构体，包含地址和长度
typedef struct uop_item {
    unsigned long addr;
    u32 len;
};

// 示例数组
struct uop_item g_item[] = {
        {100, 50},
};

// 二分查找函数
int binarySearch(unsigned long addr, u32 len)
{
    u32 left = 0, right = sizeof(g_item) / sizeof(g_item[0]);

    do {
        u32 index = (left + right) >> 1;
        struct uop_item *item = &g_item[index];

        if (addr >= (item->addr + item->len)) {
            left = index + 1;
        } else if ((addr + len) <= item->addr) {
            right = index;
        } else {
            return index;
        }
    } while (left < right);

    return -1; // 未找到，返回-1
}

1. 有重叠地址的时候就显示能找到，所以添加的时候可以使用以防止地址叠加
2. 但读写的时候，只有部分重叠地址的也显示能找到，所以拿到item之后还要检查地址是否合法

int main(int argc, char *argv[])
{
    // 要查找的地址
    int targetAddress = 95;

    // 调用二分查找函数
    int index = binarySearch(targetAddress, 2);

    if (index != -1) {
        printf("找到包含地址 %d 的结构体，索引为：%d\n", targetAddress, index);
    } else {
        printf("没有找到包含地址 %d 的结构体\n", targetAddress);
    }

    return 0;
}
