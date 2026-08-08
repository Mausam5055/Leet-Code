class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();

        vector<int> dp(n, -1);

        // We start at index 0
        dp[0] = 0;

        for (int i = 0; i < n; i++) {

            // If index i cannot be reached, skip it
            if (dp[i] == -1)
                continue;

            // Try jumping from i to every index after it
            for (int j = i + 1; j < n; j++) {

                if (abs(nums[j] - nums[i]) <= target) {

                    dp[j] = max(dp[j], dp[i] + 1);
                }
            }
        }

        return dp[n - 1];
    }
};