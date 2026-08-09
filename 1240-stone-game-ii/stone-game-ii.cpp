class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        
        // Suffix sum array
        vector<int> suffix_sum(n + 1, 0);
        for (int i = n - 1; i >= 0; --i) {
            suffix_sum[i] = suffix_sum[i + 1] + piles[i];
        }
        
        // Memoization table initialized to 0
        // M can at most be N (if a player takes N piles, M becomes N)
        vector<vector<int>> memo(n, vector<int>(n + 1, 0));
        
        // Lambda for recursion
        function<int(int, int)> dp = [&](int i, int m) {
            if (i >= n) return 0;
            if (i + 2 * m >= n) return suffix_sum[i];
            
            if (memo[i][m] != 0) return memo[i][m];
            
            int max_stones = 0;
            for (int x = 1; x <= 2 * m; ++x) {
                // Total remaining stones - Opponent's best possible score
                max_stones = max(max_stones, suffix_sum[i] - dp(i + x, max(m, x)));
            }
            
            return memo[i][m] = max_stones;
        };
        
        return dp(0, 1);
    }
};