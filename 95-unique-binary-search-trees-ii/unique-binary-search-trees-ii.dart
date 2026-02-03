class Solution {
  List<TreeNode?> generateTrees(int n) {
    if (n == 0) return [];
    return _build(1, n);
  }

  // Builds all unique BSTs for values in range [start, end]
  List<TreeNode?> _build(int start, int end) {
    List<TreeNode?> trees = [];

    // Base case: empty tree
    if (start > end) {
      trees.add(null);
      return trees;
    }

    // Try every value as root
    for (int rootVal = start; rootVal <= end; rootVal++) {
      // All possible left subtrees
      List<TreeNode?> leftTrees = _build(start, rootVal - 1);

      // All possible right subtrees
      List<TreeNode?> rightTrees = _build(rootVal + 1, end);

      // Combine left & right with current root
      for (TreeNode? left in leftTrees) {
        for (TreeNode? right in rightTrees) {
          TreeNode root = TreeNode(rootVal);
          root.left = left;
          root.right = right;
          trees.add(root);
        }
      }
    }

    return trees;
  }
}
