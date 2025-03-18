#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define ARRAY_SIZE(x) (sizeof((x)) / sizeof((x)[0]))

static int V[] = {0, 1, 3, 2, 6, 4, 5};
static vector<int> ans(7);
static stack<int> stk;

int main(int argc, char *argv[])
{
    for (int i = 1; i <= ARRAY_SIZE(V); i++) {
        while (!stk.empty() && V[stk.top()] < V[i]) {
            ans[stk.top()] = i;
            stk.pop();
        }
        stk.push(i);
    }

    for (int i = 1; i <= ARRAY_SIZE(V); i++) {
        cout << " ans: " << ans[i] << " ";
    }

    return 0;
}