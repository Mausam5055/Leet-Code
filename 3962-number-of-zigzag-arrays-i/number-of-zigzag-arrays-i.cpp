class Solution {
public:
    static const int MOD = 1e9 + 7;

    int zigZagArrays(int n, int l, int r) {
        int m = r - l + 1;
        if (m <= 1) return 0; // Edge case, though constraints say l < r

        vector<long long> up(m, 0);
        vector<long long> down(m, 0);

        // Base Case: Length = 2
        for (int i = 0; i < m; i++) {
            up[i] = i;               // Number of elements strictly less than i
            down[i] = m - 1 - i;     // Number of elements strictly greater than i
        }

        // DP transitions for length 3 to n
        for (int len = 3; len <= n; len++) {
            vector<long long> newUp(m, 0);
            vector<long long> newDown(m, 0);

            // Prefix sum for down -> transitions to newUp
            long long pref = 0;
            for (int i = 0; i < m; i++) {
                newUp[i] = pref;
                pref = (pref + down[i]) % MOD;
            }

            // Suffix sum for up -> transitions to newDown
            long long suff = 0;
            for (int i = m - 1; i >= 0; i--) {
                newDown[i] = suff;
                suff = (suff + up[i]) % MOD;
            }

            // Move to current state
            up = move(newUp);
            down = move(newDown);
        }

        // Sum up all valid arrays
        long long ans = 0;
        for (int i = 0; i < m; i++) {
            ans = (ans + up[i] + down[i]) % MOD;
        }

        return ans;
    }
};