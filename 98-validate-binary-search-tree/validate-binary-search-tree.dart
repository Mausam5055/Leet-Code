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
  bool isValidBST(TreeNode? root) {
    return _validate(root, null, null);
  }

  bool _validate(TreeNode? node, int? min, int? max) {
    // Base case: empty tree is valid
    if (node == null) return true;

    // Current node must be strictly within range
    if ((min != null && node.val <= min) ||
        (max != null && node.val >= max)) {
      return false;
    }

    // Left subtree: max bound becomes current node value
    // Right subtree: min bound becomes current node value
    return _validate(node.left, min, node.val) &&
           _validate(node.right, node.val, max);
  }
}
