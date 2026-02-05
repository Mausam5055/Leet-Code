class Solution {
    public int peopleAwareOfSecret(int n, int delay, int forget) {
        long MOD = 1_000_000_007L;
        
        long[] dp = new long[n + 1];
        dp[1] = 1; // Day 1: first person
        
        long sharing = 0; // People who can share on current day
        
        for (int day = 2; day <= n; day++) {
            
            // People who START sharing today
            if (day - delay >= 1) {
                sharing = (sharing + dp[day - delay]) % MOD;
            }
            
            // People who FORGET today (stop sharing)
            if (day - forget >= 1) {
                sharing = (sharing - dp[day - forget] + MOD) % MOD;
            }
            
            // New people who learn today
            dp[day] = sharing;
        }
        
        // Count people who still remember on day n
        long result = 0;
        for (int day = n - forget + 1; day <= n; day++) {
            if (day >= 1) {
                result = (result + dp[day]) % MOD;
            }
        }
        
        return (int) result;
    }
}
