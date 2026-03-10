class Solution {
    public int numberOfStableArrays(int zero, int one, int limit) {
        int MOD = 1_000_000_007;
        
        // dp[i][j][0] -> combinations with i zeros, j ones, ending in 0
        // dp[i][j][1] -> combinations with i zeros, j ones, ending in 1
        long[][][] dp = new long[zero + 1][one + 1][2];

        // Base cases: filling arrays with entirely 0s or 1s up to the limit
        for (int i = 1; i <= Math.min(zero, limit); i++) {
            dp[i][0][0] = 1;
        }
        for (int j = 1; j <= Math.min(one, limit); j++) {
            dp[0][j][1] = 1;
        }

        // DP population
        for (int i = 1; i <= zero; i++) {
            for (int j = 1; j <= one; j++) {
                
                // 1. Calculate for ending with 0
                dp[i][j][0] = (dp[i - 1][j][0] + dp[i - 1][j][1]) % MOD;
                if (i > limit) {
                    // Subtract the combinations that just exceeded the limit for 0s
                    dp[i][j][0] = (dp[i][j][0] - dp[i - limit - 1][j][1] + MOD) % MOD;
                }

                // 2. Calculate for ending with 1
                dp[i][j][1] = (dp[i][j - 1][0] + dp[i][j - 1][1]) % MOD;
                if (j > limit) {
                    // Subtract the combinations that just exceeded the limit for 1s
                    dp[i][j][1] = (dp[i][j][1] - dp[i][j - limit - 1][0] + MOD) % MOD;
                }
            }
        }

        // The answer is the sum of valid arrays ending in 0 and ending in 1
        return (int) ((dp[zero][one][0] + dp[zero][one][1]) % MOD);
    }
}