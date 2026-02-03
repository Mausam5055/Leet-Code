class Solution {
    fun wordBreak(s: String, wordDict: List<String>): Boolean {
        val wordSet = wordDict.toHashSet()
        val n = s.length
        val dp = BooleanArray(n + 1)

        dp[0] = true

        for (i in 1..n) {
            for (j in 0 until i) {
                if (dp[j] && wordSet.contains(s.substring(j, i))) {
                    dp[i] = true
                    break
                }
            }
        }
        return dp[n]
    }
}
