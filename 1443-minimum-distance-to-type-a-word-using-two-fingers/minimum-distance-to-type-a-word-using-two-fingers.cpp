class Solution {
public:
    int dist(int a, int b) {
        if (a == 26 || b == 26) return 0;

        int x1 = a / 6, y1 = a % 6;
        int x2 = b / 6, y2 = b % 6;

        return abs(x1 - x2) + abs(y1 - y2);
    }

    int dp[305][27][27];

    int solve(int idx, int f1, int f2, string &word) {
        if (idx == word.size()) return 0;

        int &ans = dp[idx][f1][f2];
        if (ans != -1) return ans;

        int cur = word[idx] - 'A';

        ans = min(
            dist(f1, cur) + solve(idx + 1, cur, f2, word),
            dist(f2, cur) + solve(idx + 1, f1, cur, word)
        );

        return ans;
    }

    int minimumDistance(string word) {
        memset(dp, -1, sizeof(dp));
        return solve(0, 26, 26, word);
    }
};