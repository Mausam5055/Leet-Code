class Solution {
    fun pathSum(root: TreeNode?, targetSum: Int): List<List<Int>> {
        val result = mutableListOf<List<Int>>()
        val path = mutableListOf<Int>()

        dfs(root, targetSum, path, result)
        return result
    }

    private fun dfs(
        node: TreeNode?,
        targetSum: Int,
        path: MutableList<Int>,
        result: MutableList<List<Int>>
    ) {
        if (node == null) return

        // Choose
        path.add(node.`val`)
        val remainingSum = targetSum - node.`val`

        // Check if leaf
        if (node.left == null && node.right == null && remainingSum == 0) {
            result.add(ArrayList(path)) // important: make a copy
        }

        // Explore
        dfs(node.left, remainingSum, path, result)
        dfs(node.right, remainingSum, path, result)

        // Un-choose (backtrack)
        path.removeAt(path.size - 1)
    }
}
