class Solution {
    public boolean isBalanced(TreeNode root) {
        return checkHeight(root) != -1;
    }

    private int checkHeight(TreeNode node) {
        if (node == null) return 0;

        int left = checkHeight(node.left);
        if (left == -1) return -1;  // left subtree unbalanced

        int right = checkHeight(node.right);
        if (right == -1) return -1; // right subtree unbalanced

        if (Math.abs(left - right) > 1) return -1; // current node unbalanced

        return Math.max(left, right) + 1; // return height
    }
}
