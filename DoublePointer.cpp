//
// Created by 张萍 on 2020/11/19.
//
#include "vector"
#include "unordered_map"

using namespace std;
/**
 * 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 * 示例:
    输入: [0,1,0,3,12]
    输出: [1,3,12,0,0]
 */
void moveZeroes(vector<int>& nums){
    int next_not_zero = 0, current_ptr = 0, len = nums.size();
    while (current_ptr < len) {
        if (nums[current_ptr] != 0) {
            nums[next_not_zero++] = nums[current_ptr++];
        } else {
            current_ptr++;
        }
    }
    for (int i = next_not_zero; i < len; ++i) {
        nums[i] = 0;
    }
}

/**
 * 给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组 (i, j, k, l) ，使得 A[i] + B[j] + C[k] + D[l] = 0。
 * 为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且 0 ≤ N ≤ 500 。
 * 所有整数的范围在 -2^28 到 2^28 - 1 之间，最终结果不会超过 2^31 - 1 。
 * 输入:
        A = [ 1, 2]
        B = [-2,-1]
        C = [-1, 2]
        D = [ 0, 2]
   输出:
        2
   解释:
        两个元组如下:
        1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
        2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
 */
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    // 暴力遍历，那必然是超时了
//    int len = A.size();
//    if (len == 0) return 0;
//    int result = 0;
//    int i, j, k, l;
//    for (i = 0; i < len; ++i) {
//        for (j = 0; j < len; ++j) {
//            for (k = 0;  k < len; k++) {
//                for (l = 0; l < len; l++) {
//                    if (A[i] + B[j] + C[k] + D[l] == 0) {
//                        result++;
//                    }
//                }
//            }
//        }
//    }
//    return result;
    //分组+哈希，AB一组，哈希存储A[i]+B[j]的值和出现的次数，CD同理
    int result = 0, len = A.size();
    unordered_map<int, int> mapAB;
    for (int a : A) {
        for (int b : B) {
            mapAB[a + b]++;
        }
    }
    for (int c : C) {
        for (int d : D) {
            if (mapAB.count(-c - d)) {
                result += mapAB[-c-d];
            }
        }
    }
    return result;

}

int main() {
    vector<int> vec = {0,1,0,3,12};
    moveZeroes(vec);
}
