//
// Created by 张萍 on 2020/10/22.
//
#include "iostream"
#include "vector"
#include "unordered_set"

using namespace std;
int judge(vector<vector<int>>&, int , int );
/**
 * 3 x 3 的幻方是一个填充有从 1 到 9 的不同数字的 3 x 3 矩阵，其中每行，每列以及两条对角线上的各数之和都相等。
 * 给定一个由整数组成的 grid，其中有多少个 3 × 3 的 “幻方” 子矩阵？（每个子矩阵都是连续的）。
 */
// 暴力法，可以先判断中间是不是5
int numMagicSquaresInside(vector<vector<int>>& grid) {
    int row = grid.size(); //3
    int col = grid[0].size(); //4
    if (row < 3 || col < 3) return 0;
    int count = 0;
    for (int r = 0; r <= row - 3 ; ++r) {
        for (int c = 0; c <= col - 3; ++c) {
            if (judge(grid, r, c) > 0) {
                count++;
            }
        }
    }
    return count;
}

int judge(vector<vector<int>>& grid, int row, int col) {
    unordered_set<int> set;
    int sum = grid[row][col] + grid[row][col + 1] + grid[row][col + 2];
    for (int j = 0; j <= 2; ++j) {
        if (grid[row][col+j] >9 || grid[row+1][col +j] >9 || grid[row+2][col + j] > 9) {
            return -1;
        }
        if (grid[row][col+j] <1 || grid[row+1][col +j] <1 || grid[row+2][col + j] < 1) {
            return -1;
        }
        set.insert(grid[row][col+j]);
        set.insert(grid[row+1][col+j]);
        set.insert(grid[row+2][col+j]);
        if (grid[row][col+j] + grid[row+1][col +j] + grid[row+2][col + j] != sum) {
            return -1;
        }
    }
    for (int i = 1; i <= 2; ++i) {
        if (grid[row + i][col] + grid[row+i][col + 1] + grid[row+i][col + 2]!=sum) {
            return -1;
        }
    }
    if (grid[row][col] + grid[row+1][col + 1] + grid[row+2][col + 2]!=sum) {
        return -1;
    }
    if (grid[row][col+2] + grid[row+1][col + 1] + grid[row+2][col]!=sum) {
        return -1;
    }
    return set.size()==9?1:-1;
}

int main() {
    vector<vector<int>> matrix = {{5,5,5},{5,5,5},{5,5,5}};
    cout << numMagicSquaresInside(matrix);
}