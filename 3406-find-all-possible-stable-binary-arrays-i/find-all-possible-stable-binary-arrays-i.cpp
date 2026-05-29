class Solution {
public:
    static const int MOD = 1e9 + 7;

    int dp[205][205][2];

    int solve(int zero, int one, int last, int limit) {
        if (zero == 0 && one == 0) return 1;

        if (dp[zero][one][last] != -1)
            return dp[zero][one][last];

        long long ans = 0;

        if (last == 0) {
            for (int k = 1; k <= min(limit, one); k++) {
                ans += solve(zero, one - k, 1, limit);
                ans %= MOD;
            }
        } else {
            for (int k = 1; k <= min(limit, zero); k++) {
                ans += solve(zero - k, one, 0, limit);
                ans %= MOD;
            }
        }

        return dp[zero][one][last] = ans;
    }

    int numberOfStableArrays(int zero, int one, int limit) {
        memset(dp, -1, sizeof(dp));

        long long ans = 0;

        for (int k = 1; k <= min(limit, zero); k++) {
            ans += solve(zero - k, one, 0, limit);
        }

        for (int k = 1; k <= min(limit, one); k++) {
            ans += solve(zero, one - k, 1, limit);
        }

        return ans % MOD;
    }
};