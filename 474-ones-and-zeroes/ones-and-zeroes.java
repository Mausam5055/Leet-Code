class Solution {
    public int findMaxForm(String[] strs, int m, int n) {
        
        int[][] dp = new int[m + 1][n + 1];
        
        for (String s : strs) {
            int zeros = 0, ones = 0;
            
            // count 0s and 1s
            for (char c : s.toCharArray()) {
                if (c == '0') zeros++;
                else ones++;
            }
            
            // update DP (reverse order)
            for (int i = m; i >= zeros; i--) {
                for (int j = n; j >= ones; j--) {
                    dp[i][j] = Math.max(dp[i][j], dp[i - zeros][j - ones] + 1);
                }
            }
        }
        
        return dp[m][n];
    }
}