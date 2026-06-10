class Solution {
public:
    vector<vector<int>> minAbsDiff(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> ans(m - k + 1,
                                vector<int>(n - k + 1));

        for (int r = 0; r <= m - k; r++) {
            for (int c = 0; c <= n - k; c++) {

                vector<int> vals;

                for (int i = r; i < r + k; i++) {
                    for (int j = c; j < c + k; j++) {
                        vals.push_back(grid[i][j]);
                    }
                }

                sort(vals.begin(), vals.end());

                vals.erase(unique(vals.begin(), vals.end()),
                           vals.end());

                if (vals.size() <= 1) {
                    ans[r][c] = 0;
                    continue;
                }

                int mn = INT_MAX;

                for (int i = 1; i < vals.size(); i++) {
                    mn = min(mn, vals[i] - vals[i - 1]);
                }

                ans[r][c] = mn;
            }
        }

        return ans;
    }
};