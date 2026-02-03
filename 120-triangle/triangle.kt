class Solution {
    fun minimumTotal(triangle: List<List<Int>>): Int {
        val n = triangle.size
        
        // Copy last row as initial DP
        val dp = triangle[n - 1].toMutableList()
        
        // Start from second last row and move upwards
        for (i in n - 2 downTo 0) {
            for (j in 0..i) {
                dp[j] = triangle[i][j] + minOf(dp[j], dp[j + 1])
            }
        }
        
        return dp[0]
    }
}
