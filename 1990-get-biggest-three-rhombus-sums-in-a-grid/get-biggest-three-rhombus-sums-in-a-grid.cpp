class Solution {
public:
    vector<int> getBiggestThree(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();

        vector<vector<int>> d1(m + 1, vector<int>(n + 2, 0));
        vector<vector<int>> d2(m + 1, vector<int>(n + 2, 0));

        // ↘ diagonal prefix
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                d1[i + 1][j + 1] = d1[i][j] + grid[i][j];

        // ↙ diagonal prefix
        for (int i = 0; i < m; i++)
            for (int j = n - 1; j >= 0; j--)
                d2[i + 1][j] = d2[i][j + 1] + grid[i][j];

        auto getD1 = [&](int x1, int y1, int x2, int y2) {
            return d1[x2 + 1][y2 + 1] - d1[x1][y1];
        };

        auto getD2 = [&](int x1, int y1, int x2, int y2) {
            return d2[x2 + 1][y2] - d2[x1][y1 + 1];
        };

        set<int, greater<int>> st;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                st.insert(grid[i][j]); // radius 0

                int lim = min({i, m - 1 - i, j, n - 1 - j});

                for (int k = 1; k <= lim; k++) {
                    int sum = 0;

                    sum += getD2(i - k, j, i, j - k);
                    sum += getD1(i, j - k, i + k, j);
                    sum += getD2(i, j + k, i + k, j);
                    sum += getD1(i - k, j, i, j + k);

                    // remove duplicated corners
                    sum -= grid[i - k][j];
                    sum -= grid[i][j - k];
                    sum -= grid[i][j + k];
                    sum -= grid[i + k][j];

                    st.insert(sum);
                }
            }
        }

        vector<int> ans;
        for (int x : st) {
            ans.push_back(x);
            if (ans.size() == 3) break;
        }
        return ans;
    }
};