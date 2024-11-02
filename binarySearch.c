#include <stdio.h>

// 定义结构体，包含地址和长度
typedef struct {
    int address; // 地址
    int length;  // 长度
} Range;

// 二分查找函数
int binarySearch(Range arr[], int left, int right, int targetAddress) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        // 检查目标地址是否在当前结构体的地址范围内
        if (targetAddress >= arr[mid].address && targetAddress <= (arr[mid].address + arr[mid].length - 1)) {
            return mid; // 找到，返回索引
        } else if (targetAddress < arr[mid].address) {
            right = mid - 1; // 在左半边继续查找
        } else {
            left = mid + 1; // 在右半边继续查找
        }
    }
    return -1; // 未找到，返回-1
}

int main() {
    // 示例数组
    Range ranges[] = {
        {100, 50},
        {200, 30},
        {250, 20},
        {300, 40}
    };
    int n = sizeof(ranges) / sizeof(ranges[0]);
    
    // 要查找的地址
    int targetAddress = 225;
    
    // 调用二分查找函数
    int index = binarySearch(ranges, 0, n - 1, targetAddress);
    
    if (index != -1) {
        printf("找到包含地址 %d 的结构体，索引为：%d\n", targetAddress, index);
    } else {
        printf("没有找到包含地址 %d 的结构体\n", targetAddress);
    }
    
    return 0;
}
