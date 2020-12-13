//
// Created by 张萍 on 2020/11/26.
//
#include "iostream"
#include "algorithm"
#include "vector"
#include "limits"
using namespace std;

/**
 * 给定一个无序的数组，找出数组在排序之后，相邻元素之间最大的差值。
 * 如果数组元素个数小于 2，则返回 0。
 */
// 暴力解法：排序+遍历
int maximumGap(vector<int> & nums) {
    if (nums.size() < 2 ) return 0;
    sort(nums.begin(), nums.end());
    int maxGap = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
        if (nums[i + 1] - nums[i] > maxGap) {
            maxGap = nums[i + 1] - nums[i];
        }
    }
    return maxGap;
}

//为保证时间和空间的线性要求，学习桶排序
int maximumGapBucket(vector<int>& nums) {
    if (nums.size() < 2) {
        return 0;
    }
    int min_num = INT_MAX, max_num = -1;
    for (int num : nums) { // 找到最大最小值
        if (num < min_num) min_num = num;
        if (num > max_num) max_num = num;
    }
    int bucket_gap = max(int ((max_num - min_num)/(nums.size() - 1)), 1);// 计算每个桶的间距, 让每个桶是等距的
    int bucket_num = (max_num - min_num)/bucket_gap + 1; // 计算桶的数量

}

int main() {

}
