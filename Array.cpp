//
// Created by 张萍 on 2020/11/28.
//
#include "limits"
#include "iostream"
#include "vector"
#include "algorithm"
#include "unordered_map"


using namespace std;
int find_reverse_pairs(vector<int>& nums, int left, int right) {
    int res = 0, mid = (right + left) / 2;
    int i = left, j = mid + 1;
    for (;i <= mid; i++) {
        while (j <= right && (long)nums[i] > 2 * (long)nums[j]) {
            res += mid - i + 1;
            j++;
        }
    }
    return res;
}
int merge_sorted(vector<int>& nums, vector<int>& nums_sorted, int left, int right) {
    if (left >= right) return 0;
    int mid = (right + left) / 2;
    int res = merge_sorted(nums, nums_sorted, left, mid) +
              merge_sorted(nums, nums_sorted, mid + 1, right) +
              find_reverse_pairs(nums, left, right);
    int i = left, j = mid + 1, index = left;
    while (i <= mid && j <= right) {
        if (nums[i] <= nums[j]) nums_sorted[index++] = nums[i++];
        else nums_sorted[index++] = nums[j++];
    }
    while (i <= mid) nums_sorted[index++] = nums[i++];
    while (j <= right) nums_sorted[index++] = nums[j++];

    for (int ind = left; ind <= right; ++ind) {
        nums[ind] = nums_sorted[ind];
    }
    return res;

}
/**
 * 给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。
 * 你需要返回给定数组中的重要翻转对的数量。
 */
int reversePairs(vector<int>& nums) {
    //暴力解法,数溢出了，且会超时
    int result = 0, len = nums.size();
    if (len <= 1) return 0;
    vector<int> nums_sorted(len, 0);
    return merge_sorted(nums, nums_sorted, 0, len - 1);
}

/**
 * 给定由一些正数（代表长度）组成的数组 A，返回由其中三个长度组成的、面积不为零的三角形的最大周长。
 * 如果不能形成任何面积不为零的三角形，返回 0。
 */
int largestPerimeter(vector<int>& A) {
    sort(A.begin(),A.end());
    int len = A.size();
    for (int i = len - 1; i >= 2 ; --i) {
        if (A[i - 2] + A[i - 1] > A[i]) {
            return A[i - 2] + A[i - 1] + A[i];
        }
    }
    return 0;
}

/**
 * 给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
 * 如果数组中不存在目标值 target，返回 [-1, -1]。
 * 二分查找 O(log n)
 * e.g. nums = [5,7,7,8,8,10], target = 8
 */
int findLeftBound(vector<int> & nums, int target);
int findRightBound(vector<int> & nums, int target);
vector<int> searchRange(vector<int>& nums, int target) {
    if (nums.empty()) return {-1, -1};
    int left = findLeftBound(nums, target), right = findRightBound(nums, target);
    return {left, right};
}
int findLeftBound(vector<int> & nums, int target) {
    int len = nums.size();
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (target > nums[mid]) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (left != len && nums[left] == target) return left;
    return -1;
}
int findRightBound(vector<int> & nums, int target) {
    int len = nums.size();
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (target < nums[mid]) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    if (right < 0 || left == len) return -1;
    return nums[right] == target ? right : -1;
}

/**
 * 给你一个整数数组 nums ，请你将数组按照每个值的频率 升序 排序。如果有多个值的频率相同，请你按照数值本身将它们 降序 排序。
 * 请你返回排序后的数组。
 */
// 学习了匿名函数[捕获参数](参数列表)->返回类型{函数体}
vector<int> frequencySort(vector<int>& nums) {
    unordered_map<int, int> counts;
    for (int i : nums) {
        if (counts.count(i) == 0) {
            counts[i] = 1;
        } else {
            counts[i] = counts[i] + 1;
        }
    }
    int min = INT_MAX;
    sort(nums.begin(), nums.end(), [&counts](int a, int b) {
        if (counts[a] != counts[b]) {
            return counts[a] < counts[b];
        } else {
            return a > b;
        }
    });
    return nums;
}

int main() {
    vector<int> nums = {1,2,3,4};
    frequencySort(nums);
}