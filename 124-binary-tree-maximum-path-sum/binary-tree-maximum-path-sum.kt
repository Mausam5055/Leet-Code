class Solution {

    private var maxSum = Int.MIN_VALUE

    fun maxPathSum(root: TreeNode?): Int {
        dfs(root)
        return maxSum
    }

    private fun dfs(node: TreeNode?): Int {
        if (node == null) return 0

        // Max downward path from left & right
        val left = maxOf(0, dfs(node.left))
        val right = maxOf(0, dfs(node.right))

        // Path passing through current node
        val currentPath = node.`val` + left + right

        // Update global maximum
        maxSum = maxOf(maxSum, currentPath)

        // Return max downward path to parent
        return node.`val` + maxOf(left, right)
    }
}
