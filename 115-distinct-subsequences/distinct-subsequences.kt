class Solution {
    fun numDistinct(s: String, t: String): Int {
        val m = s.length
        val n = t.length

        val dp = Array(m + 1) { IntArray(n + 1) }

        // Base case: empty t
        for (i in 0..m) {
            dp[i][0] = 1
        }

        for (i in 1..m) {
            for (j in 1..n) {
                dp[i][j] = dp[i - 1][j]  // skip s[i-1]
                if (s[i - 1] == t[j - 1]) {
                    dp[i][j] += dp[i - 1][j - 1] // use s[i-1]
                }
            }
        }

        return dp[m][n]
    }
}
