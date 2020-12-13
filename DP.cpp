//
// Created by 张萍 on 2020/11/26.
//
#include "vector"
#include "iostream"

using namespace std;

/**
 * 一个N x N的网格(grid) 代表了一块樱桃地，每个格子由以下三种数字的一种来表示：
        0 表示这个格子是空的，所以你可以穿过它。
        1 表示这个格子里装着一个樱桃，你可以摘到樱桃然后穿过它。
        -1 表示这个格子里有荆棘，挡着你的路。
 * 你的任务是在遵守下列规则的情况下，尽可能的摘到最多樱桃：
        从位置 (0, 0) 出发，最后到达 (N-1, N-1) ，只能向下或向右走，并且只能穿越有效的格子（即只可以穿过值为0或者1的格子）；
        当到达 (N-1, N-1) 后，你要继续走，直到返回到 (0, 0) ，只能向上或向左走，并且只能穿越有效的格子；
        当你经过一个格子且这个格子包含一个樱桃时，你将摘到樱桃并且这个格子会变成空的（值变为0）；
        如果在 (0, 0) 和 (N-1, N-1) 之间不存在一条可经过的路径，则没有任何一个樱桃能被摘到。
 */
//四维动态数组？太难了 741题
int cherryPickup(vector<vector<int>>& grid) {
    int N = grid.size();
    if(N == 0) return 0;
    vector<vector<int>> dp(N + 1, vector<int>(N + 1,0));
    dp[N][N] = -1;
    //先往下,往右走第一趟
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= N; ++j) {
            if (grid[i - 1][j - 1] == -1) { //这里是荆棘，那么
                dp[i][j] = 0;
            } else if (grid[i - 1][j - 1] == 0) {
                dp[i][j];
            }
        }
    }
    return 0;
}

/**
 * 一个机器人位于一个 m(列) x n(行) 网格的左上角 （起始点在下图中标记为“Start” ）。
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。
 * 问总共有多少条不同的路径？
 * 7 x 3 指三行七列
 */
int uniquePaths(int m, int n) {
    int dp[n][m];
    for (int i = 0; i < m; ++i) {
        dp[0][i] = 1;
    }
    for (int j = 1; j < n; ++j) {
        dp[j][0] = 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[n - 1][m - 1];
}

int main() {

}