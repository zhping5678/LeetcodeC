//
// Created by 张萍 on 2020/12/8.
//
#include "iostream"
#include "vector"
#include "limits"

using namespace std;

/**
 * 给定一个数字字符串 S，比如 S = "123456579"，我们可以将它分成斐波那契式的序列 [123, 456, 579]。
 * 形式上，斐波那契式序列是一个非负整数列表 F，且满足：
        0 <= F[i] <= 2^31 - 1，（也就是说，每个整数都符合 32 位有符号整数类型）；
        F.length >= 3；
        对于所有的0 <= i < F.length - 2，都有 F[i] + F[i+1] = F[i+2] 成立。
 * 另外，请注意，将字符串拆分成小块时，每个块的数字一定不要以零开头，除非这个块是数字 0 本身。
 * 返回从 S 拆分出来的任意一组斐波那契式的序列块，如果不能拆分则返回 []。
 */ // DFS + 回溯
bool trace_back(vector<int>& res, string s, int len, int index, int pre, long long sum) {
    if (index == len) { //到结尾了
        return res.size() >= 3;
    }
    long long curr = 0;
    for (int i = index; i < len; ++i) {
        if (i > index && s[index] == '0') { //如果分出来的数不是0(i>index)，且首位是0，不满足
            break;
        }
        curr = curr * 10 + (s[i] - '0');
        if (curr > INT_MAX) {
            break;
        }
        if (res.size() >= 2) { //如果已经有值了
            if (curr > sum) {//如果大于，已经不可能满足 curr == sum（pre1+pre2）
                break;
            } else if (curr < sum) { //curr还需要继续往后划分扩大
                continue;
            }//curr == sum就往下，push_back到res中
        }
        res.push_back(curr);
        if (trace_back(res, s, len, i + 1, (int)curr, pre + curr)) {
            return true;
        }
        res.pop_back(); //以上划分不满足，pop，重新划分
    }
    return false;
}
vector<int> splitIntoFibonacci(string S) {
    vector<int> result;
    trace_back(result, S, S.size(), 0,0,0);
    return result;
}

int main() {
    string S = "123456579";
    splitIntoFibonacci(S);
}
