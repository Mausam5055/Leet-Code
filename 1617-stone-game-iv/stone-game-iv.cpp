class Solution {
public:
    bool winnerSquareGame(int n) {
        // dp[i] represents if the current player can win with i stones remaining
        vector<bool> dp(n + 1, false);
        
        for (int i = 1; i <= n; ++i) {
            // Check all possible square numbers we can subtract
            for (int k = 1; k * k <= i; ++k) {
                // If taking away k*k stones puts the opponent in a losing state,
                // then the current state i is a winning state.
                if (!dp[i - k * k]) {
                    dp[i] = true;
                    break; // We only need one winning move
                }
            }
        }
        
        return dp[n];
    }
};