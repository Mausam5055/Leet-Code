class Solution {
    public int numDistinct(String s, String t) {
        int m = s.length();
        int n = t.length();
        
        // dp[i][j] represents the number of times t[0...j-1] appears in s[0...i-1]
        int[][] dp = new int[m + 1][n + 1];
        
        // Base case: An empty string 't' is a subsequence of any 's' exactly 1 time
        for (int i = 0; i <= m; i++) {
            dp[i][0] = 1;
        }
        
        // Fill the DP table
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (s.charAt(i - 1) == t.charAt(j - 1)) {
                    // Match found: Add ways by USING this character + ways by IGNORING it
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                } else {
                    // No match: We can only ignore the current character in 's'
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        
        return dp[m][n];
    }
}