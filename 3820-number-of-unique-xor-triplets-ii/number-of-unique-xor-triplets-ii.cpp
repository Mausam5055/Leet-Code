class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int v : nums) {
            for (int cnt = 2; cnt >= 0; --cnt) {
                for (int x = 0; x < MAXX; ++x) {
                    if (dp[cnt][x]) {
                        dp[cnt + 1][x ^ v] = true;
                    }
                }
            }
        }

        vector<bool> seen(MAXX, false);

        // Triplets with repeated indices give existing values only.
        for (int v : nums)
            seen[v] = true;

        // Triplets with three distinct indices.
        for (int x = 0; x < MAXX; ++x)
            if (dp[3][x])
                seen[x] = true;

        int ans = 0;
        for (bool ok : seen)
            ans += ok;

        return ans;
    }
};