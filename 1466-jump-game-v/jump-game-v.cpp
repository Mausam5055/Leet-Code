class Solution {
public:
    vector<int> dp;

    int dfs(int i, vector<int>& arr, int d) {
        if (dp[i] != -1)
            return dp[i];

        int ans = 1;

        // Left
        for (int j = i - 1; j >= max(0, i - d); j--) {
            if (arr[j] >= arr[i])
                break;
            ans = max(ans, 1 + dfs(j, arr, d));
        }

        // Right
        for (int j = i + 1; j <= min((int)arr.size() - 1, i + d); j++) {
            if (arr[j] >= arr[i])
                break;
            ans = max(ans, 1 + dfs(j, arr, d));
        }

        return dp[i] = ans;
    }

    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        dp.assign(n, -1);

        int ans = 1;

        for (int i = 0; i < n; i++)
            ans = max(ans, dfs(i, arr, d));

        return ans;
    }
};