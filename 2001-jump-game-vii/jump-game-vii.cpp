class Solution {
public:
    bool canReach(string s, int minJump, int maxJump) {
        int n = s.size();

        vector<bool> dp(n, false);
        dp[0] = true;

        int pre = 0;

        for (int i = 1; i < n; i++) {
            if (i - minJump >= 0)
                pre += dp[i - minJump];

            if (i - maxJump - 1 >= 0)
                pre -= dp[i - maxJump - 1];

            if (s[i] == '0' && pre > 0)
                dp[i] = true;
        }

        return dp[n - 1];
    }
};