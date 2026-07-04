class Solution {
public:
    int numberOfSubmatrices(vector<vector<char>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> prefX(m, vector<int>(n, 0));
        vector<vector<int>> prefY(m, vector<int>(n, 0));

        int ans = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                prefX[i][j] = (grid[i][j] == 'X');
                prefY[i][j] = (grid[i][j] == 'Y');

                if (i > 0) {
                    prefX[i][j] += prefX[i - 1][j];
                    prefY[i][j] += prefY[i - 1][j];
                }

                if (j > 0) {
                    prefX[i][j] += prefX[i][j - 1];
                    prefY[i][j] += prefY[i][j - 1];
                }

                if (i > 0 && j > 0) {
                    prefX[i][j] -= prefX[i - 1][j - 1];
                    prefY[i][j] -= prefY[i - 1][j - 1];
                }

                if (prefX[i][j] > 0 && prefX[i][j] == prefY[i][j])
                    ans++;
            }
        }

        return ans;
    }
};