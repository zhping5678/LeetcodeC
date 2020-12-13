//
// Created by 张萍 on 2020/9/15.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <sstream>
//#include <math.h>
#include "cmath"
#include "hash_map"

using namespace std;

/**
 * 给定一个整数数组nums和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。
 * 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
 * @param nums
 * @param target
 * @return
 */
vector<int> twoSumI(vector<int>& nums, int target) {
    vector<int> result(0);
    int len = nums.size();
    for (int i = 0; i < len - 1; ++i) {
        for (int j = i + 1; j < len; ++j) {
            if(nums[i] + nums[j] == target) {
                result.push_back(i);
                result.push_back(j);
                return result;
            }
        }
    }
    return result;
}

vector<int> twoSumII(vector<int>& nums, int target) {
    int len = nums.size();
    unordered_map<int, int> hash_map;
    for (int i = 0; i < len; ++i) {
        auto it = hash_map.find(target - nums[i]);
        if (it != hash_map.end()) {
            cout << it->first << ", " << it->second;
            return {i, it->second}; //it.first equals it.key in java and it.second equals it.value
        }
        hash_map[nums[i]] = i;
    }
    return {};
}

/**
 * 给定一个正整数，返回它在 Excel 表中相对应的列名称。
 * 例如，
    1 -> A
    2 -> B
    3 -> C
    ...
    26 -> Z
    27 -> AA
    28 -> AB
    ...
 * @return
 */
string convertToTitle(int n) {
    string res;
    int curr = n;
    while (curr != 0) {
        curr--;
        res.push_back('A' + curr % 26);
        curr = curr / 26;
    }
    reverse(res.begin(), res.end());
    return res;
}

vector<int> constructRectangle(int area) {
    int square_root = sqrt(area);
    int w = square_root, l = area/w;
    while (w * l != area) {
        w--;
        l = area/w;
    }
    return {l, w};
}

/**
 * 给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
 * 示例 1
 * 输入: s = "anagram", t = "nagaram"
 * 输出: true
 */
bool isAnagram(string s, string t) { //表驱动
    if (s.size() != t.size()) return false;
    vector<int> frequency(26, 0);
    for (char c : s) {
        frequency[c - 'a']++;
    }
    for (char c : t) {
        frequency[c - 'a']--;
        if (frequency[c - 'a'] < 0) {
            return false;
        }
    }
    for (int f : frequency) {
        if (f != 0) return false;
    }
    return true;
}

/**
 * 给你一个字符串 s ，请你根据下面的算法重新构造字符串：
 * 从 s 中选出 最小 的字符，将它 接在 结果字符串的后面。
 * 从 s 剩余字符中选出 最小 的字符，且该字符比上一个添加的字符大，将它 接在 结果字符串后面。
 * 重复步骤 2 ，直到你没法从 s 中选择字符。
 * 从 s 中选出 最大 的字符，将它 接在 结果字符串的后面。
 * 从 s 剩余字符中选出 最大 的字符，且该字符比上一个添加的字符小，将它 接在 结果字符串后面。
 * 重复步骤 5 ，直到你没法从 s 中选择字符。
 * 重复步骤 1 到 6 ，直到 s 中所有字符都已经被选过。
 * 在任何一步中，如果最小或者最大字符不止一个 ，你可以选择其中任意一个，并将其添加到结果字符串。
 * 请你返回将 s 中字符重新排序后的 结果字符串 。
 * 示例 1：
        输入：s = "aaaabbbbcccc"
        输出："abccbaabccba"
        解释：第一轮的步骤 1，2，3 后，结果字符串为 result = "abc"
        第一轮的步骤 4，5，6 后，结果字符串为 result = "abccba"
        第一轮结束，现在 s = "aabbcc" ，我们再次回到步骤 1
        第二轮的步骤 1，2，3 后，结果字符串为 result = "abccbaabc"
        第二轮的步骤 4，5，6 后，结果字符串为 result = "abccbaabccba"
 */
string sortString(string s) {
    if (s.size() <= 1) {
        return s;
    }
    int len = s.size();
    vector<int> frequency(26,0);
    for (char c : s) {
        frequency[c - 'a'] = frequency[c - 'a'] + 1;
    }
    string ss;
    while (ss.size() != len) {
        for (int i = 0; i < 26; ++i) {
            if (frequency[i] > 0) {
                ss.push_back('a' + i);
                frequency[i]--;
            }
        }
        for (int i = 25; i >= 0 ; --i) {
            if (frequency[i] > 0) {
                ss.push_back('a' + i);
                frequency[i]--;
            }
        }
    }
    return ss;
}
/**
 * 给你一个字符串 sequence ，如果字符串 word 连续重复 k 次形成的字符串是 sequence 的一个子字符串，那么单词 word 的 重复值为 k 。
 * 单词 word 的 最大重复值 是单词 word 在 sequence 中最大的重复值。如果 word 不是 sequence 的子串，那么重复值 k 为 0 。
 * 给你一个字符串 sequence 和 word ，请你返回 最大重复值 k 。
 */
int maxRepeating(string sequence, string word) {
    if (word.size() > sequence.size()) return 0;
    int maxR = (int)(sequence.size() / word.size());
    string tmp = word;
    int i;
    for (i = 1; i <= maxR ; ++i) {
        if (sequence.find(tmp) == string::npos) return i - 1;
        tmp = tmp + word;
    }
    return i - 1;

}

bool judgePrimes(int n) {
    for (int i = 2;i * i <= n ;i++) {
        if (n % i == 0) return false;
    }
    return true;
}
/**
 * 统计小于n的质数的个数
 */
// 常规写法
int countPrimes(int n) {
    int count = 0;
    for (int i = 2; i < n; ++i) {
        cout << i << ": " << judgePrimes(i) << endl;
        if (judgePrimes(i)) count++;
    }
    return count;

}
// 埃氏筛，一个数x是质数，那么x的倍数一定不是质数
// 应该直接从x⋅x开始标记,因为 2x,3x……这些数一定在x·x之前就被其他数的倍数标记过了,例如2的所有倍数，3的所有倍数等
int countPrimesByAiShiShai(int n) {
    vector<int> isPrime(n, 1);
    int count = 0;
    for (int i = 2; i < n; ++i) {
        if (isPrime[i]) { //这个位置是质数，那么他的倍数都是合数，isPrime应该置0
            count++;
            if ((long long)i * i < n) {
                for (int j = i * i; j < n; j = j + i) {
                    isPrime[j] = 0;
                }
            }
        }
    }
    return count;
}

/**
 * 给定一个非负整数 numRows，生成杨辉三角的前 numRows 行
 *     1
 *    1 1
 *   1 2 1
 *  1 3 3 1
 * 1 4 6 4 1
 */
vector<vector<int>> generate(int numRows) {
    vector<vector<int>> result(0);
    if (numRows == 0) {
        return result;
    }
    result.emplace_back(1,1);
    for (int i = 2; i <= numRows; ++i) {
        vector<int> row;
        row.push_back(1);
        vector<int> preRow = result.back();
        for (int j = 1; j < i - 1; ++j) {
            row.push_back(preRow[j] + preRow[j - 1]);
        }
        row.push_back(1);
        result.push_back(row);
    }
    return result;
}

/**
 * 在柠檬水摊上，每一杯柠檬水的售价为 5 美元。
 * 顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。
 * 每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。
 * 注意，一开始你手头没有任何零钱。
 * 如果你能给每位顾客正确找零，返回 true ，否则返回 false 
 */
bool lemonadeChange(vector<int>& bills) {
    int five_count = 0, ten_count = 0;
    for (int bill : bills) {
        if (bill == 5) {
            five_count++;
            continue;
        }
        if (bill == 10) {
            if (five_count <= 0) return false;
            ten_count++;
            five_count--;
            continue;
        }
        if (bill == 20) {
            if (five_count <= 0) return false;
            if (ten_count > 0) {
                ten_count--;
                five_count--;
            } else if (five_count >= 3) {
                five_count = five_count - 3;
            } else {
                return false;
            }
        }
    }
    return true;
}
int numberOfMatches(int n) {
    if (n <= 2) return n / 2;
    int result = 0;
    while (n != 1) {
        result = result + (n / 2);
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = (n + 1) / 2;
        }
    }
    return result;
}

int minPartitions(string n) {
    int result = 0;
    int preMax = 0;
    for (int i : n) {
        int curr = i - 48;
        if (curr > preMax) {
            result = result + (curr - preMax);
            preMax = curr;
        }
    }
    return result;
}

int main() {
    vector<int> vec = {3,5,8,10};
    string s = "ababc";
    string w = "ba";
    generate(5);
//    cout << countPrimes(10);
//    cout << maxRepeating(s, w);
}