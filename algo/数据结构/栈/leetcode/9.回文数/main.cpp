#include <iostream>

using namespace std;

static string int2str(int x) // 将int类型转成字符串
{
    string str;

    while (x != 0) {
        str.push_back((x % 10) + '0');
        x /= 10;
    }

    return str;
}

class Solution {
public:
    bool isPalindrome(int x)
    {
        string str;
        int len;

        if (x <= 0) {
            return x == 0;
        }

        str = int2str(x);
        len = str.size();

        for (int i = 0; i <= len / 2; i++) {
            if (str[i] != str[len - i - 1]) {
                return false;
            }
        }
        return true;
    }
};

int main(int argc, char *argv[])
{
    Solution s;
    int x = 0;

    cout << "result=" << s.isPalindrome(x) << endl;

    return 0;
}
