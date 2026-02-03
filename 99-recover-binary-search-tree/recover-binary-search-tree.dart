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
  TreeNode? first;
  TreeNode? second;
  TreeNode? prev;

  void recoverTree(TreeNode? root) {
    _inorder(root);

    // Swap the values of the two incorrect nodes
    int temp = first!.val;
    first!.val = second!.val;
    second!.val = temp;
  }

  void _inorder(TreeNode? node) {
    if (node == null) return;

    _inorder(node.left);

    // Detect violation
    if (prev != null && prev!.val > node.val) {
      if (first == null) {
        first = prev;
      }
      second = node;
    }

    prev = node;

    _inorder(node.right);
  }
}
