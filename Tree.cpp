//
// Created by 张萍 on 2020/11/18.
//
#include "iostream"
#include "vector"
#include "queue"

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class BinaryTree {
public:
    /**
     * 给定一个有 N 个节点的二叉树，每个节点都有一个不同于其他节点且处于 {1, ..., N} 中的值。
     * 通过交换节点的左子节点和右子节点，可以翻转该二叉树中的节点。
     * 考虑从根节点开始的先序遍历报告的 N 值序列。将这一 N 值序列称为树的行程。
     * 我们的目标是翻转最少的树中节点，以便树的行程与给定的行程 voyage 相匹配。 
     * 如果可以，则返回翻转的所有节点的值的列表。你可以按任何顺序返回答案。
     * 如果不能，则返回列表 [-1]。
     */
    vector<int> result;
    int index = 0;
    bool dfs(TreeNode* root,vector<int>& voyage) {
        if (root == nullptr || index >= voyage.size()){
            return true;
        }
        if (root->val != voyage[index]) {
            return false;
        }
        index++;
        //先序遍历，先左
        if(root->left != nullptr && root->left->val != voyage[index]) { //左节点不匹配，尝试翻转
            result.push_back(root->val);
            return dfs(root->right, voyage) && dfs(root->left, voyage);
        } else { // 左节点为空或者匹配,继续匹配右节点
            return dfs(root->left, voyage) && dfs(root->right, voyage);
        }
    }
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        if (dfs(root, voyage)) {
            return result;
        }
        return {-1};
    }

    /**
     * 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
     * 最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
     * 满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
     */
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr || root == p || root == q) return root;
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left == nullptr) return right;
        if (right == nullptr) return left;
        return root;
    }

    /** 34题
     * 输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。
     */
    vector<vector<int>> paths;
    vector<int> currentPath;
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (root == nullptr) return paths;
        int rootVal = root->val;
        currentPath.push_back(rootVal);
        int newSum = sum - rootVal;
        if (newSum == 0 && root->left == nullptr && root->right == nullptr) {
            paths.push_back(currentPath);
        }
        pathSum(root->left, newSum);
        pathSum(root->right, newSum);
        currentPath.pop_back();
        return paths;
    }

};

class CompleteBinaryTree{
public:
    /**
     * 给出一个完全二叉树，求出该树的节点个数。
     * 说明：完全二叉树的定义如下：在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，
     *      并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第 h 层，则该层包含 1~ 2h 个节点。
     */
     int countNodes(TreeNode* root) {
         if (nullptr == root) {
             return 0;
         }
         queue<TreeNode*> q;
         q.push(root->left);
         q.push(root->right);
         int count = 1;
         while (!q.empty()) {
             TreeNode* curr = q.front();
             if (curr != nullptr) {
                 q.push(curr->left);
                 q.push(curr->right);
                 count++;
             } else {
                 return count;
             }
             q.pop();
         }
        return count;
     }
};

int main() {
    //[5,4,8,11,null,13,4,7,2,null,null,5,1]
    //22
    TreeNode root(5);
    TreeNode node1_1(4);
    TreeNode node1_2(8);
    TreeNode node2_1(11);
    TreeNode node2_2(13);
    TreeNode node2_3(4);

    TreeNode node3_1(7);
    TreeNode node3_2(2);
    TreeNode node3_3(5);
    TreeNode node3_4(1);
    root.left = &node1_1;
    root.right = &node1_2;

    node1_1.left = &node2_1;
    node1_2.left = &node2_2;
    node1_2.right = &node2_3;

    node2_1.left = &node3_1;
    node2_1.right = &node3_2;
    node2_3.left = &node3_3;
    node2_3.right = &node3_4;
    BinaryTree binaryTree;
    binaryTree.pathSum(&root, 22);
}