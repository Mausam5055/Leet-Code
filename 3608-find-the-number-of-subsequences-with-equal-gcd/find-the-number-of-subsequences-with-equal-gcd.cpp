class Solution {
public:
    static const int MOD = 1e9 + 7;

    int subsequencePairCount(vector<int>& nums) {
        const int MAX = 200;

        // Precompute gcds
        int G[201][201];
        for (int i = 0; i <= MAX; i++)
            for (int j = 0; j <= MAX; j++)
                G[i][j] = std::gcd(i, j);

        vector<vector<int>> dp(MAX + 1, vector<int>(MAX + 1, 0));
        dp[0][0] = 1;

        for (int x : nums) {
            vector<vector<int>> ndp = dp;

            for (int g1 = 0; g1 <= MAX; g1++) {
                for (int g2 = 0; g2 <= MAX; g2++) {
                    long long cur = dp[g1][g2];
                    if (!cur) continue;

                    int ng1 = (g1 == 0 ? x : G[g1][x]);
                    ndp[ng1][g2] = (ndp[ng1][g2] + cur) % MOD;

                    int ng2 = (g2 == 0 ? x : G[g2][x]);
                    ndp[g1][ng2] = (ndp[g1][ng2] + cur) % MOD;
                }
            }

            dp.swap(ndp);
        }

        long long ans = 0;
        for (int g = 1; g <= MAX; g++) {
            ans = (ans + dp[g][g]) % MOD;
        }

        return (int)ans;
    }
};