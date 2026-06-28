class Solution {
public:
    int maximumAmount(vector<vector<int>>& coins) {
        int m = coins.size(), n = coins[0].size();

        const int NEG = -1e9;

        vector<vector<vector<int>>> dp(
            m, vector<vector<int>>(n, vector<int>(3, NEG)));

        // Starting cell
        if (coins[0][0] >= 0) {
            dp[0][0][0] = coins[0][0];
        } else {
            dp[0][0][0] = coins[0][0]; // don't neutralize
            dp[0][0][1] = 0;           // neutralize
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) continue;

                for (int k = 0; k <= 2; k++) {

                    // From top
                    if (i > 0 && dp[i-1][j][k] != NEG) {
                        if (coins[i][j] >= 0)
                            dp[i][j][k] = max(dp[i][j][k],
                                              dp[i-1][j][k] + coins[i][j]);
                        else {
                            dp[i][j][k] = max(dp[i][j][k],
                                              dp[i-1][j][k] + coins[i][j]);

                            if (k < 2)
                                dp[i][j][k+1] = max(dp[i][j][k+1],
                                                    dp[i-1][j][k]);
                        }
                    }

                    // From left
                    if (j > 0 && dp[i][j-1][k] != NEG) {
                        if (coins[i][j] >= 0)
                            dp[i][j][k] = max(dp[i][j][k],
                                              dp[i][j-1][k] + coins[i][j]);
                        else {
                            dp[i][j][k] = max(dp[i][j][k],
                                              dp[i][j-1][k] + coins[i][j]);

                            if (k < 2)
                                dp[i][j][k+1] = max(dp[i][j][k+1],
                                                    dp[i][j-1][k]);
                        }
                    }
                }
            }
        }

        return max({dp[m-1][n-1][0],
                    dp[m-1][n-1][1],
                    dp[m-1][n-1][2]});
    }
};