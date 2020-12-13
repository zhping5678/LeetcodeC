//
// Created by 张萍 on 2020/11/17.
//
#include <iostream>
#include <vector>
using namespace std;

/**
 * 给定一个字符串 (s) 和一个字符模式 (p) ，实现一个支持 '?' 和 '*' 的通配符匹配。
   '?' 可以匹配任何单个字符。
   '*' 可以匹配任意字符串（包括空字符串）。
 * 两个字符串完全匹配才算匹配成功。
 * 说明:
    s 可能为空，且只包含从 a-z 的小写字母。
    p 可能为空，且只包含从 a-z 的小写字母，以及字符 ? 和 *。
*/
bool isMatchByDP(string s, string p) { //动态规划
    int s_len = s.size(), p_len = p.size();
    vector<vector<int>> dp(s_len + 1, vector<int>(p_len + 1, 0));
    dp[0][0] = 1;
    // 先考虑dp矩阵边界，即空串，*可以匹配空串，当p的前i个字符全是*时，可以匹配任意s
    for (int k = 1; k <= p_len; ++k) {
        if(p[k - 1] != '*') {
            break;
        }
        dp[0][k] = 1;
    }
    // 现在考虑不明白
    for (int i = 1; i <= s_len; ++i) {
        for (int j = 1; j <= p_len ; ++j) {
            if (p[j - 1] == '*') {
                dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            } else if(p[j - 1] == '?' || p[j - 1] == s[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            }
        }
    }
    return dp[s_len][p_len];
}
// 双指针贪心算法
bool isMatchByGreedy(string s, string p) {
    int ptr_s = 0, ptr_p = 0, s_star = -1, p_star = -1, s_len = s.size(), p_len = p.size(); // x_star代表*号的位置
    while (ptr_s < s_len) {
        if (ptr_p < p_len && p[ptr_p] == '?' || s[ptr_s] == p[ptr_p]) {
            ptr_p++; ptr_s++; //如果字符匹配，指针后移
        } else if (ptr_p < p_len && p[ptr_p] == '*') { //如果字符不匹配,且p中是*,标记x_star的位置
            p_star = ptr_p; s_star = ptr_s;
            ptr_p++; //p中指针后移
        } else if (s_star >= 0) { //如果字符不匹配，p也不是*号，那么看是不是有s_star可以匹配
            //这个时候要把p中的指针移到 p_star下一位，等*号匹配结束,接着匹配p和s
            ptr_p = p_star + 1;
            ptr_s = s_star + 1;
            s_star++;
        } else { //以上情况都不是
            return false;
        }
    }
    //匹配完之后，p中不能剩除了*外的字符
    while (ptr_p < p_len) {
        if (p[ptr_p] == '*') ptr_p++;
        else break;
    }
    return ptr_p == p_len;
}

/**
 *我们将相邻字母都相同的一串字符定义为相同字母组，例如："h", "eee", "ll", "ooo"。
 * 对于一个给定的字符串S，如果另一个单词能够通过将一些字母组扩张从而使其和S相同，我们将这个单词定义为可扩张的（stretchy）。
 * 扩张操作定义如下：选择一个字母组（包含字母c），然后往其中添加相同的字母c使其长度达到 3 或以上。
 * 输入一组查询单词，输出其中可扩张的单词数量。
 *
 * 示例：
 * 输入： S = "heeellooo", words = ["hello", "hi", "helo"]
 * 输出：1
 * 解释：
 * 我们能通过扩张 "hello" 的 "e" 和 "o" 来得到 "heeellooo"。
 * 我们不能通过扩张 "helo" 来得到 "heeellooo" 因为 "ll" 的长度小于 3 。
 */
bool judgeStretchy(const string& s, const string& origin) {
    int ptr_s = 0, ptr_ori = 0, count_s = 0, count_ori = 0;
    char current_ch;
    bool flag = true;
    while  (ptr_s < s.size() && ptr_ori < origin.size()) {
        if (s[ptr_s] != origin[ptr_ori]) {
            flag = false;
            break;
        }
        current_ch = s[ptr_s];
        count_s = count_ori = 0;
        while (ptr_s < s.size() && s[ptr_s] == current_ch) {
            count_s++; ptr_s++;
        }
        while (ptr_ori < origin.size() && origin[ptr_ori] == current_ch) {
            count_ori++; ptr_ori++;
        }
        // ==原本一样不用扩充
        if (count_ori != count_s && (count_s < 3 || count_s < count_ori)) {
            flag = false;
            break;
        }
    }
    return flag && ptr_s == s.size() && ptr_ori == origin.size();
}
int expressiveWords(string S, vector<string>& words) {
    int count = 0;
    for (const string& word : words) {
        if (judgeStretchy(S, word)) count++;
    }
    return count;
}

int main() {
    isMatchByGreedy("adcbed","a*b?b");
}


