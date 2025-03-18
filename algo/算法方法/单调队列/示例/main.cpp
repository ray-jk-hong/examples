#include <iostream>
#include <deque>

using namespace std;

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

static int V[] = {0, 1, 3, 6, 2, 5, 1, 7};
static int m = 3; // 表示划窗大小

int main(int argc, char *argv[])
{
    deque<int> dqe;
    for (int i = 1; i <= ARRAY_SIZE(V); i++) {
        if (!dqe.empty() && ((i - dqe.front()) >= m)) { // 1. 计算窗口大小，先把窗口外的队列前向出队
            dqe.pop_front();
        }
        while (!dqe.empty() && V[dqe.back()] < V[i]) { // 2. 扫描队列，将小于V[i]的从队列中后向出队
            dqe.pop_back();
        }
        dqe.push_back(i); // 3. 将下标放到队列中
        if (i >= m - 1) {
            cout << V[dqe.front()] << " ";
        }
    }
    return 0;
}