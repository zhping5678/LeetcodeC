//
// Created by 张萍 on 2020/11/30.
//
#include "iostream"
#include "unordered_map"
#include "vector"
#include "algorithm"
using namespace std;
/**
 * 给定一个字符串S，检查是否能重新排布其中的字母，使得两相邻的字符不同。
 * 若可行，输出任意可行的结果。若不可行，返回空字符串。
 */
string reorganizeString(string S) {
    if (S.size() <= 1) return S;
    vector<int> count(26,0);
    int maxTime = 0, len = S.size();
    for (char c : S) {
        count[c - 'a']++;
        maxTime = max(maxTime, count[c - 'a']);
    }
    if (maxTime > (len + 1)/2) {
        return "";
    }
    string result(len,' ');
    int evenIndex = 0, oddIndex = 1;
    for (int i = 0; i < 26; ++i) {
        char c = 'a' + i;
        while (count[i] > 0 && count[i] <= len/2 && oddIndex < len) { //字母出现的次数不超过长度一半，隔着放在奇数下标，不会挨上
            result[oddIndex] = c;
            oddIndex+=2;
            count[i]--;
        }
        while (count[i] > 0) { //不满足上面的条件：长度为(len+1)/2 或 奇数位置放满了，开始放偶数
            result[evenIndex] = c;
            evenIndex+=2;
            count[i]--;
        }
    }
    return result;
}

string interpret(string command) {
    string res;
    for (int i = 0;i < command.size();i++) {
        if (command[i] == 'G') {
            res+=command[i];
        } else { //只能是(
            if (command[i + 1] == ')') {
                res+='o';
                i++;
            } else { //al
                res+="al";
                i = i + 3;
            }
        }
    }
    return res;
}

/**
 * 给你一个整数数组 nums 和一个整数 k 。
 * 每一步操作中，你需要从数组中选出和为 k 的两个整数，并将它们移出数组。
 * 返回你可以对数组执行的最大操作数。
 */
int maxOperations(vector<int>& nums, int k) {
    if (nums.size() < 2) return 0;
    sort(nums.begin(), nums.end());
    int count = 0;
    int ptr1 = 0, ptr2 = nums.size() - 1;
    while (ptr1 < ptr2) {
        if (nums[ptr1] + nums[ptr2] == k) {
            count++;
            ptr1++;// 移除说明每个数字只能用一次
            ptr2--;
        } else if (nums[ptr1] + nums[ptr2] > k) { //大了，大数往小
            ptr2--;
        } else { //和小了，小数往大
            ptr1++;
        }
    }
    return count;
}

/**
 * 给你一个整数数组 nums​​​ 和一个整数 k 。你需要将这个数组划分到 k 个相同大小的子集中，使得同一个子集里面没有两个相同的元素。
 * 一个子集的 不兼容性 是该子集里面最大值和最小值的差。
 * 请你返回将数组分成 k 个子集后，各子集 不兼容性 的 和 的 最小值 ，如果无法分成分成 k 个子集，返回 -1 。
 * 子集的定义是数组中一些数字的集合，对数字顺序没有要求。
 */ //5619
int minimumIncompatibility(vector<int>& nums, int k) {
    int len = nums.size();
    if (len % k != 0) return -1;
    int preSize = len / k;
    sort(nums.begin(), nums.end());
    vector<int> isAllocated(len, 1);
    vector<vector<int>> buckets(k, vector<int>(0));
    for (int i = 0; i < len; ++i) {
        
    }
}

string convertToBinary(int n) {
    string s;
    int i = n;
    while (i != 0) {
        char ch = (i % 2) == 0 ? '0' : '1';
        s+=ch;
        i = i / 2;
    }
    return s;
}
/**
 * 给你一个整数 n ，请你将 1 到 n 的二进制表示连接起来，并返回连接结果对应的 十进制 数字对 10^9 + 7 取余的结果。
 */
int concatenatedBinary(int n) {
    string res;
    for (int i = 1; i <= n; ++i) {
        res.append(convertToBinary(i));
    }

}