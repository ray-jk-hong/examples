#include <iostream>
#include <string>
#include <vector>:

using namespace std;

class Solution {
public:
    string removeDuplicateLetters(string s) {
        // vis(26)用来存储是否存在栈中，当布尔型用
        // num(26)用来存储字符的个数。
        // 值得一提的是，ch - 'a'这种形式直接将26个不同小写字母变成索引，a是nums[0],b是nums[1]诸如此类。同理要是想把字符串中是数字的字符转换成整型，只要ch - '0' 就可以得到对应的整数。
        vector<int> vis(26), nums(26);
        // 计算字符个数。
        for(auto ch : s) {
            nums[ch - 'a'] ++; 
        }
        // 用来当作结果的字符串，用来当栈用。
        string res;
        for (auto ch : s) {
            // 准备添加的字符没有出现过
            if (!vis[ch - 'a']) {
                // 栈不为空，且准备加入的字符小于栈顶元素（字典序逆序）
                while (!res.empty() && res.back() > ch) {
                    // 栈顶元素是重复的
                    if(nums[res.back() - 'a'] > 0){
                        // 将该栈顶元素重新标为未visited的
                        vis[res.back() - 'a'] = 0;
                        // 弹出栈顶元素
                        res.pop_back();
                    } else {
                        break;
                    }
                }
                // 将即将加入的字符标为visited
                vis[ch - 'a'] = 1;
                //入栈。
                res += ch;
            }
            // 将新加入的字符的剩余数量减1
            nums[ch - 'a'] -= 1;
        }
        return res;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    string str = "cbacdcbc";
    string res;

    res = s.removeDuplicateLetters(str);
    cout << res << endl;
    return 0;
}