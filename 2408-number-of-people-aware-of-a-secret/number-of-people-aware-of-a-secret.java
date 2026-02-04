class Solution {
    public int peopleAwareOfSecret(int n, int delay, int forget) {
        long MOD = 1_000_000_007;
        long[] dp = new long[n + 1]; // dp[i] = number of people who discovered the secret on day i
        dp[1] = 1;
        
        long sharing = 0; // Number of people currently sharing the secret
        
        for (int i = 2; i <= n; i++) {
            // 1. Add people who start sharing today (discovered it 'delay' days ago)
            if (i - delay >= 1) {
                sharing = (sharing + dp[i - delay]) % MOD;
            }
            
            // 2. Remove people who forget today (discovered it 'forget' days ago)
            if (i - forget >= 1) {
                sharing = (sharing - dp[i - forget] + MOD) % MOD;
            }
            
            // 3. The current sharers tell new people
            dp[i] = sharing;
        }
        
        // Calculate total people who still know the secret
        // (Everyone who discovered it in the last 'forget' days)
        long totalAware = 0;
        for (int i = n - forget + 1; i <= n; i++) {
            if (i >= 1) {
                totalAware = (totalAware + dp[i]) % MOD;
            }
        }
        
        return (int) totalAware;
    }
}