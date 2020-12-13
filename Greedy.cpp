//
// Created by 张萍 on 2020/11/23.
//
#include <algorithm>
#include <vector>
#include <iostream>
#include "unordered_map"
#include "queue"
using namespace std;

/**
 * 在二维空间中有许多球形的气球。对于每个气球，提供的输入是水平方向上，气球直径的开始和结束坐标。由于它是水平的，所以纵坐标并不重要，因此只要知道开始和结束的横坐标就足够了。
 * 开始坐标总是小于结束坐标。一支弓箭可以沿着 x 轴从不同点完全垂直地射出。
 * 在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart ≤ x ≤ xend，则该气球会被引爆。
 * 可以射出的弓箭的数量没有限制。 弓箭一旦被射出之后，可以无限地前进。我们想找到使得所有气球全部被引爆，所需的弓箭的最小数量。
 * 给你一个数组 points ，其中 points {i} = {xstart,xend} ，返回引爆所有气球所必须射出的最小弓箭数.
 * 示例 1：
 *      输入：points = {{10,16},{2,8},{1,6},{7,12}}
 *      输出：2
 *      解释：对于该样例，x = 6 可以射爆 {2,8},{1,6} 两个气球，以及 x = 11 射爆另外两个气球
 */
bool compare(vector<int> ball1, vector<int> ball2) {
    return ball1[1] < ball2[1];
}
//逻辑应该没有问题，但是erase操作太耗时了
int findMinArrowShots(vector<vector<int>>& points) {
    if (points.size() <= 1) {
        return points.size();
    }
    sort(points.begin(), points.end(), compare);
    for (auto p : points) {
        cout<< "start: " << p[0] << ", stop: " << p[1] << endl;
    }
    int result = 0;
    while (!points.empty()) {
        int arrow = points[0][1];
        auto it = points.begin();
        for (;it != points.end();) {
            if ((*it)[0] <= arrow && arrow <= (*it)[1]) {
                points.erase(it);
            } else {
                it++;
            }
        }
        result++;
    }
    return result;
}
// 题解，思想差不多
int findMinArrowShotsII(vector<vector<int>>& points) {
    if (points.size() <= 1) {
        return points.size();
    }
    sort(points.begin(), points.end(), compare);
    int arrow_pos = points[0][1]; //右边界最左的球
    int result = 1;// 上面这个已经是一个答案了
    for (auto ball : points) {
        if (ball[0] > arrow_pos) { //因为已经排好序了，如果这个射不到了，那这个ball是剩下球里右边界最小的了
            arrow_pos = ball[1];
            result++;
        }
    }
    return result;
}

/**
 * 给定一个以字符串表示的非负整数 num，移除这个数中的 k 位数字，使得剩下的数字最小。
 */
// 遍历，从左到右，丢弃掉比左边大的数，只留小的数字
string removeKdigits(string num, int k) {
    vector<char> queue;
    for (auto& digit : num) {
        // 看看有没有比digit大的，有就弹出，然后把自己加进去,前提是还没丢够k个
        while (!queue.empty() && k > 0 && queue.back() > digit) {
            queue.pop_back();
            k--;
        }
        queue.push_back(digit);
    }
    //k > 0，说明num是递增/不降的，把后面的元素接着弹出
    while (k > 0) {
        queue.pop_back();
        k--;
    }
    //把结果拼起来
    string result = "";
    bool isLeadingZero = true;
    for (auto& digit : queue) {
        if (digit == '0' && isLeadingZero) { //还是前面的0
            continue;
        }
        isLeadingZero = false;
        result+=digit;
    }
    return result.empty() ? "0" : result;
}

/**
 * 给定长度分别为 m 和 n 的两个数组，其元素由 0-9 构成，表示两个自然数各位上的数字。
 * 现在从这两个数组中选出 k (k <= m + n) 个数字拼接成一个新的数，要求从同一个数组中取出的数字保持其在原数组中的相对顺序。
 * 求满足该条件的最大数。结果返回一个表示该最大数的长度为 k 的数组。
 * 说明: 请尽可能地优化你算法的时间和空间复杂度。
 */
vector<int> maxSubSequence(vector<int>& nums, int k);
vector<int> mergeSequence(vector<int>& nums1, vector<int>& nums2);
int compare(vector<int> nums1, int index1, vector<int> nums2, int index2);
vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    int m = nums1.size(), n = nums2.size();
    int start = max(0, k - n), end = min(m, k);
    vector<int> maxSequence(k,0);
    // 分别找到两个数组的最大值
    for (int i = start; i <= end; ++i) {
        vector<int> subSequence1(maxSubSequence(nums1,i));
        vector<int> subSequence2(maxSubSequence(nums2, k - i));
        // 把两个结果合并成最大的序列
        vector<int> currentMaxSeq = mergeSequence(subSequence1, subSequence2);
        if (compare(currentMaxSeq,0, maxSequence,0) > 0) {
            maxSequence.assign(currentMaxSeq.begin(), currentMaxSeq.end());
        }
    }
    return maxSequence;
}
vector<int> maxSubSequence(vector<int>& nums, int k) { //在nums数组中挑出k个数，使子序列最大
    int len = nums.size();
    vector<int> queue;
    int count = len - k; //要扔掉的数字
    for (int i : nums) {
        while (!queue.empty() && count > 0 && queue.back() < i) {
            queue.pop_back();
            count--;
        }
        queue.push_back(i);
    }
    while (count > 0) {
        queue.pop_back();
        count--;
    }
    return queue;
}
//合并两个数组
vector<int> mergeSequence(vector<int>& nums1, vector<int>& nums2) {
    int len1 = nums1.size(), len2 = nums2.size();
    if (len1 == 0) return nums2;
    if (len2 == 0) return nums1;
    vector<int> result(len1 + len2, 0);
    int index1 = 0, index2 = 0, i = 0;
    for (; i < len1 + len2; i++) {
        if (compare(nums1, index1, nums2, index2) > 0) {
            result[i] = nums1[index1++];
        } else {
            result[i] = nums2[index2++];
        }
    }
    return result;
}
//比较两个数组
int compare(vector<int> nums1, int index1, vector<int> nums2, int index2) {
    int len1 = nums1.size(), len2 = nums2.size();
    while (index1 < len1 && index2 < len2) {
        int minus = nums1[index1++] - nums2[index2++];
        if (minus != 0) return minus;
    }
    return (len1 - index1) - (len2 - index2); //运行到这里说明前面都一样，看谁长
}

/**
 * 给你一个按升序排序的整数数组 num（可能包含重复数字），请你将它们分割成一个或多个子序列，其中每个子序列都由连续整数组成且长度至少为 3 。
 * 如果可以完成上述分割，则返回 true ；否则，返回 false 。
 * 示例 1：
 *      输入: [1,2,3,3,4,5] 输出: True
 *      解释:你可以分割出这样两个连续子序列 : [1, 2, 3],[3, 4, 5]
 */
//map+最小堆：键是序列最后一个数字，值是这样的序列长度数组（以最小堆存放）
bool isPossibleI(vector<int>& nums) {
    unordered_map<int, priority_queue<int, vector<int>, greater<>>> mp;
    for (int i : nums) {
        if (mp.count(i) == 0) {
            mp[i] = priority_queue<int, vector<int>, greater<>>();
        }
        if (mp.count(i - 1) == 0) { //没有以i为结尾的序列，重新构造一个
            mp[i].push(1);
        } else { //有以i-1为结尾的序列，找到长度最小的，加进去，现在键值变成i了
            int preMinLen = mp[i - 1].top();
            mp[i - 1].pop();
            if (mp[i - 1].empty()) mp.erase(i - 1);
            mp[i].push(preMinLen + 1);
        }
    } // 划分结束
    for (auto & it : mp) {
        if (it.second.top() < 3) {
            return false;
        }
    }
    return true;
}

//用两个hashmap，一个存储剩余数字的个数，一个存储以key为结尾的序列个数
bool isPossibleII(vector<int>& nums) {
    unordered_map<int, int> countMap;
    for (int i : nums) {
        countMap[i]++;
    }
    unordered_map<int, int> tailCountMap;
    for (int x : nums) {
        if (countMap[x] <= 0) continue; //只有有剩余才处理
        if (tailCountMap[x - 1] == 0) { //目前没有以x-1为结尾的序列
            //要以x为开头新起一个队列，就要判断x+1 和 x+2 还有没有剩余，保证长度不小于3
            if (countMap[x + 1] <= 0 || countMap[x + 2] <= 0) return false;
            countMap[x]--;
            countMap[x + 1]--;
            countMap[x + 2]--;
            tailCountMap[x + 2]++;
        } else { //有以x - 1为结尾的序列
            tailCountMap[x]++;
            tailCountMap[x - 1]--;
            countMap[x]--;
        }
    }
    return true;
}

/**
 * 给你一个用字符数组 tasks 表示的 CPU 需要执行的任务列表。其中每个字母表示一种不同种类的任务。
 * 任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。
 * 在任何一个单位时间，CPU 可以完成一个任务，或者处于待命状态。
 * 然而，两个相同种类的任务之间必须有长度为整数 n 的冷却时间，因此至少有连续n个单位时间内CPU在执行不同的任务，或者在待命状态。
 * 你需要计算完成所有任务所需要的 最短时间 。
 */
// 桶排序
// A B C F
// A B C F
// A B C F
// A B D
// A B D
// A B
int leastInterval(vector<char>& tasks, int n) {
    int len = tasks.size(); // 也是桶的数量，每个桶的容量为n+1
    vector<int> vec(26); // 计数
    for(char c : tasks) {
        ++vec[c-'A'];
    }
    sort(vec.begin(),vec.end(),[](int& x,int&y){return x>y;}); //降序排列
    int cnt=1;
    while(cnt<vec.size()&&vec[cnt]==vec[0]) { //vec[0]是出现次数最多的任务数
        cnt++; //最后一个桶的任务数
    }
    return max(len,cnt+(n+1)*(vec[0]-1));
}

/**
 * 有一个二维矩阵 A 其中每个元素的值为 0 或 1 。
 * 移动是指选择任一行或列，并转换该行或列中的每一个值：将所有 0 都更改为 1，将所有 1 都更改为 0。
 * 在做出任意次数的移动后，将该矩阵的每一行都按照二进制数来解释，矩阵的得分就是这些数字的总和。
 * 返回尽可能高的分数。
 * 示例：
    输入：[[0,0,1,1],[1,0,1,0],[1,1,0,0]]
    输出：39
    解释：
    转换为 [[1,1,1,1],[1,0,0,1],[1,1,1,1]]
    0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
 */
// 保证每一行最左是1：翻转最左不是1的行；
// 翻转0对于1的列
// 翻转过程中动态计算分数总和
int matrixScore(vector<vector<int>>& A) {
    int row_num = A.size(), col_num = A[0].size();
    int result = 0;
    for (int i = 0; i < row_num; ++i) {
        if (A[i][0] == 0) { //最左是0，翻转该行
            for (int j = 0; j < col_num; ++j) {
                A[i][j] = A[i][j] == 0 ? 1 : 0;
            }
        }
    }
    //这时最左都是1，每一行最左的值是2^(col_num - 1)
    result = row_num * (1 << (col_num - 1));
    //查看每一列，如果列中0比1多，翻转
    int countOne;
    for (int col = 1; col < col_num; ++col) {
        countOne = 0;
        for (int row = 0; row < row_num; ++row) {
            countOne += A[row][col];
        }
        int k = max(countOne, row_num - countOne);
        result += k * (1 << (col_num - col - 1));
    }
    return result;
} //但是其实可以不用翻转最左端是0的行，只要在遍历每一列的时候判断一下


/**
 * Dota2 的世界里有两个阵营：Radiant(天辉)和 Dire(夜魇)，Dota2 参议院由来自两派的参议员组成。
 * 现在参议院希望对一个 Dota2 游戏里的改变作出决定。他们以一个基于轮为过程的投票进行。
 * 在每一轮中，每一位参议员都可以行使两项权利中的一项：
 *      禁止一名参议员的权利：参议员可以让另一位参议员在这一轮和随后的几轮中丧失所有的权利。
 *      宣布胜利：如果参议员发现有权利投票的参议员都是同一个阵营的，他可以宣布胜利并决定在游戏中的有关变化。
 * 给定一个字符串代表每个参议员的阵营。字母 “R” 和 “D” 分别代表了 Radiant（天辉）和 Dire（夜魇）。
 * 如果有 n 个参议员，给定字符串的大小将是 n。
 * 以轮为基础的过程从给定顺序的第一个参议员开始到最后一个参议员结束。这一过程将持续到投票结束。所有失去权利的参议员将在过程中被跳过。
 * 假设每一位参议员都足够聪明，会为自己的政党做出最好的策略，你需要预测哪一方最终会宣布胜利并在 Dota2 游戏中决定改变。
 * 输出应该是 Radiant 或 Dire。
 */
// 双队列模拟循环队列，存议员的发言序号
string predictPartyVictory(string senate) {
    int n = senate.size();
    queue<int> radiant, dire;
    for (int i = 0; i < n; ++i) {
        if (senate[i] == 'R') radiant.push(i);
        else dire.push(i);
    } //入队
    while (!radiant.empty() && !dire.empty()) {
        //看谁先发言，一定会永久弹出对方阵营的第一个人，自己回到队尾
        if (radiant.front() < dire.front()) {
            radiant.push(radiant.front() + n);
        } else {
            dire.push(dire.front() + n);
        }
        radiant.pop();
        dire.pop();
    }
    return radiant.empty() ? "Dire" : "Radiant";
}

/**
 * 如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。
 * 第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。
 * 例如， [1,7,4,9,2,5] 是一个摆动序列，因为差值 (6,-3,5,-7,3) 是正负交替出现的。
 * 相反, [1,4,7,2,5] 和 [1,7,4,5,5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。
 * 给定一个整数序列，返回作为摆动序列的最长子序列的长度。
 * 通过从原始序列中删除一些（也可以不删除）元素来获得子序列，剩下的元素保持其原始顺序。
 */
//贪心
int wiggleMaxLength(vector<int>& nums) {
    int n = nums.size();
    if (n < 2) {
        return n;
    }
    int prevdiff = nums[1] - nums[0];
    int ret = prevdiff != 0 ? 2 : 1;
    for (int i = 2; i < n; i++) {
        int diff = nums[i] - nums[i - 1];
        if ((diff > 0 && prevdiff <= 0) || (diff < 0 && prevdiff >= 0)) {
            ret++;
            prevdiff = diff;
        }
    }
    return ret;
}
//贪心+动态规划 我觉得这个更好理解一点
int wiggleMaxLengthDP(vector<int>& nums) {
    int down = 1, up = 1;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] > nums[i - 1])
            up = down + 1;
        else if (nums[i] < nums[i - 1])
            down = up + 1;
    }
    return nums.empty() ? 0 : max(down, up);
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
//    vector<vector<int>> points = {{0,9},{1,8},{7,8},{1,6},{9,16},{7,13},{7,10},{6,11},{6,9},{9,13}};
//    cout << findMinArrowShotsII(points);
    vector<char> tasks = {'A','A','A','A','A','A','B','C','D','E','F','G'};
    string s = "27346209830709182346";
    vector<int> stones = {7,90,5,1,100,10,10,2};
}

