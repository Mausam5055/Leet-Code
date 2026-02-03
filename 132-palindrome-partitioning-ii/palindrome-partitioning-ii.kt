class Solution {
    fun minCut(s: String): Int {
        val n = s.length
        val isPal = Array(n) { BooleanArray(n) }
        
        // Build palindrome table
        for (i in n - 1 downTo 0) {
            for (j in i until n) {
                if (s[i] == s[j] && (j - i <= 2 || isPal[i + 1][j - 1])) {
                    isPal[i][j] = true
                }
            }
        }
        
        val dp = IntArray(n) { Int.MAX_VALUE }
        
        for (i in 0 until n) {
            if (isPal[0][i]) {
                dp[i] = 0
            } else {
                for (j in 1..i) {
                    if (isPal[j][i]) {
                        dp[i] = minOf(dp[i], dp[j - 1] + 1)
                    }
                }
            }
        }
        
        return dp[n - 1]
    }
}
