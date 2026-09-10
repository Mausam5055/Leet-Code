/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int averageOfSubtree(TreeNode* root) {
        int matchingNodes = 0;
        postOrder(root, matchingNodes);
        return matchingNodes;
    }

private:
    // Returns a pair: {sum_of_subtree, count_of_nodes}
    std::pair<int, int> postOrder(TreeNode* node, int& matchingNodes) {
        if (!node) {
            return {0, 0}; 
        }

        auto left = postOrder(node->left, matchingNodes);
        auto right = postOrder(node->right, matchingNodes);

        int currentSum = left.first + right.first + node->val;
        int currentCount = left.second + right.second + 1;

        // Integer division automatically rounds down to nearest integer in C++
        if (node->val == currentSum / currentCount) {
            matchingNodes++;
        }

        return {currentSum, currentCount};
    }
};