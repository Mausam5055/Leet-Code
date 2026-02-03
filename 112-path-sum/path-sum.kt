class Solution {
    fun hasPathSum(root: TreeNode?, targetSum: Int): Boolean {
        // Base case: empty tree
        if (root == null) return false

        // If this is a leaf node
        if (root.left == null && root.right == null) {
            return root.`val` == targetSum
        }

        // Reduce targetSum and check left or right subtree
        val remainingSum = targetSum - root.`val`

        return hasPathSum(root.left, remainingSum) ||
               hasPathSum(root.right, remainingSum)
    }
}
