class Solution {
    fun sumNumbers(root: TreeNode?): Int {
        return dfs(root, 0)
    }

    private fun dfs(node: TreeNode?, current: Int): Int {
        if (node == null) return 0

        val newSum = current * 10 + node.`val`

        // If this is a leaf node, return the formed number
        if (node.left == null && node.right == null) {
            return newSum
        }

        // Otherwise, sum from left and right subtrees
        return dfs(node.left, newSum) + dfs(node.right, newSum)
    }
}
