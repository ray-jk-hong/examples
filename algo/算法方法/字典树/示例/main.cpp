#include <iostream>
#include <vector>

// 前缀树保存字符串的列表，可以快速查询字符串是否存在. 还可以统计某个字符串前缀总共出现了几次等信息
// 前缀树的表示方式有两种，一种是数组，另外一种是链表
// 1. 数组方式存储前缀树
// https://blog.csdn.net/Keep_Trying_Go/article/details/127028174

// 2. 链表方式 
struct Trie {
    int val;
    Trie *next[26];
    Trie(void) {
        memset(next, 0, sizeof(Trie *) * 26);
    }
};

int main(int argc, char *argv[])
{
    return 0;
}