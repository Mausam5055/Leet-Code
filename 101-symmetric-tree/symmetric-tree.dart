/**
 * Definition for a binary tree node.
 * class TreeNode {
 *   int val;
 *   TreeNode? left;
 *   TreeNode? right;
 *   TreeNode([this.val = 0, this.left, this.right]);
 * }
 */

class Solution {
  bool isSymmetric(TreeNode? root) {
    if (root == null) return true;
    return _isMirror(root.left, root.right);
  }

  bool _isMirror(TreeNode? left, TreeNode? right) {
    // Both null → symmetric
    if (left == null && right == null) return true;

    // One null → not symmetric
    if (left == null || right == null) return false;

    // Values must match
    if (left.val != right.val) return false;

    // Check mirrored children
    return _isMirror(left.left, right.right) &&
           _isMirror(left.right, right.left);
  }
}
