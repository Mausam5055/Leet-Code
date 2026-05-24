class Solution {
public:
    vector<int> dp;
    int n;

    int dfs(int i, vector<int>& arr, int d) {
        if (dp[i] != -1) return dp[i];

        int ans = 1; // count current index

        // Left jumps
        for (int j = i - 1; j >= max(0, i - d); j--) {
            if (arr[j] >= arr[i]) break;
            ans = max(ans, 1 + dfs(j, arr, d));
        }

        // Right jumps
        for (int j = i + 1; j <= min(n - 1, i + d); j++) {
            if (arr[j] >= arr[i]) break;
            ans = max(ans, 1 + dfs(j, arr, d));
        }

        return dp[i] = ans;
    }

    int maxJumps(vector<int>& arr, int d) {
        n = arr.size();
        dp.assign(n, -1);

        int result = 1;

        for (int i = 0; i < n; i++) {
            result = max(result, dfs(i, arr, d));
        }

        return result;
    }
};