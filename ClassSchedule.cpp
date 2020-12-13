//
// Created by 张萍 on 2020/10/23.
//
#include "vector"
#include "hash_set"
#include "queue"

using namespace std;
/**
 * 你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。
 * 在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]
 * 给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？
 *
 * 示例 1:
 * 输入: 2, [[1,0]]
 * 输出: true
 * 解释: 总共有 2 门课程。学习课程 1 之前，你需要完成课程 0。所以这是可能的。
 *
 * 示例 2:
 * 输入: 2, [[1,0],[0,1]]
 * 输出: false
 * 解释: 总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0；并且学习课程 0 之前，你还应先完成课程 1。这是不可能的。
 *
 * 提示：
 * 输入的先决条件是由 边缘列表 表示的图形，而不是 邻接矩阵 。详情请参见图的表示法。
 * 你可以假定输入的先决条件中没有重复的边。
 * 1 <= numCourses <= 10^5
 */
// 入度表+邻接表 ---- 广度优先遍历
bool canFinishI(int numCourses, vector<vector<int>>& prerequisites) {
    int indegrees[numCourses]; //入度表
    vector<vector<int>> adjacency(numCourses); //邻接表
    queue<int> q;// 入度为零的队列
    //初始化一下
    for (int i = 0; i < numCourses; ++i) {
        indegrees[i] = 0;
    }
    for (auto & prerequisite : prerequisites) { //构造入度表和邻接表
        indegrees[prerequisite[0]]++;
        adjacency[prerequisite[1]].push_back(prerequisite[0]);
    }
    //入度为0的加到queue
    for (int i = 0;i < numCourses;i++) {
        if (indegrees[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int pre = q.front(); //删除入度为0的点，同时删除该点的edge==邻接表中相邻节点的入度-1
        q.pop();
        numCourses--;
        for (int curr : adjacency[pre]) {
            indegrees[curr]--;
            if (indegrees[curr] == 0) q.push(curr);
        }
    }
    return numCourses == 0;
}
// dfs搜索
bool dfs(vector<vector<int>>& adjacency, vector<int>& flags, int i) {
    if (flags[i] == -1) return true;
    if (flags[i] == 1) return false;
    flags[i] = 1;
    for (int j : adjacency[i]) {
        if (!dfs(adjacency, flags, j)) return false;
    }
    flags[i] = -1;
    return true;
}
// 邻接表+访问标志位dfs搜索 ----- 深度优先遍历
bool canFinishII(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> flags(numCourses, 0);// 0：没访问过  -1：被其他节点起始的搜索访问过（说明走通过了，无环） 1：被当前节点起始的搜索访问两次（有环）
    vector<vector<int>> adjacency(numCourses); //邻接表
    for (auto & prerequisite : prerequisites) { //构造邻接表
        adjacency[prerequisite[1]].push_back(prerequisite[0]);
    }
    for (int j = 0; j < numCourses; ++j) {
        if(!dfs(adjacency, flags, j)) return false;
    }
    return true;
}

/**
 * 现在你总共有 n 门课需要选，记为 0 到 n-1。
 * 在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]
 * 给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。
 * 可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。
 */
// 找到一个拓扑排序？
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> indegrees(numCourses, 0); //入度表
    vector<vector<int>> adjacency(numCourses, vector<int>(0)); //邻接表
    queue<int> degree0;
    vector<int> order(0);
    //构造表
    for (auto & prerequisite : prerequisites) {
        indegrees[prerequisite[0]]++;
        adjacency[prerequisite[1]].push_back(prerequisite[0]);
    }
    //找到入度为零的节点，加入队列，随后删除，同时删除相连的边
    for (int i = 0; i < numCourses; ++i) {
        if (indegrees[i] == 0) {
            degree0.push(i);
            order.push_back(i);
        }
    }
    while (!degree0.empty()) {
        int nodeToDel = degree0.front();
        degree0.pop();
        for (int i : adjacency[nodeToDel]) {
            indegrees[i]--;
            if (indegrees[i] == 0) {
                degree0.push(i);
                order.push_back(i);
            }
        }
    }
    if (order.size() == numCourses) return order;
    return {};
}

/**
 * 这里有 n 门不同的在线课程，他们按从 1 到 n 编号。每一门课程有一定的持续上课时间（课程时间）t 以及关闭时间第 d 天。
 * 一门课要持续学习 t 天直到第 d 天时要完成，你将会从第 1 天开始。
 * 给出 n 个在线课程用 (t, d) 对表示。你的任务是找出最多可以修几门课。
 *
 * 输入: [[100, 200], [200, 1300], [1000, 1250], [2000, 3200]]
 * 输出: 3
 * 解释: 这里一共有 4 门课程, 但是你最多可以修 3 门:
 *      修第一门课时, 它要耗费 100 天，你会在第 100 天完成, 在第 101 天准备下门课。
 *      修第三门课时, 它会耗费 1000 天，所以你将在第 1100 天的时候完成它, 以及在第 1101 天开始准备下门课程。
 *      修第二门课时, 它会耗时 200 天，所以你将会在第 1300 天时完成它。
 *      第四门课现在不能修，因为你将会在第 3300 天完成它，这已经超出了关闭日期。
 */
// EDF调度思想，deadline早的优先
int scheduleCourse(vector<vector<int>>& courses) {

}