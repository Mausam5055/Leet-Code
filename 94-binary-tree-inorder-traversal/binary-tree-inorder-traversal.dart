class Solution {
  List<int> inorderTraversal(TreeNode? root) {
    List<int> result = [];

    void dfs(TreeNode? node) {
      if (node == null) return;

      dfs(node.left);       // Left
      result.add(node.val); // Root
      dfs(node.right);      // Right
    }

    dfs(root);
    return result;
  }
}
