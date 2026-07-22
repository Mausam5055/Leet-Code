class Solution {
public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        int count = 0;
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Add the sum from the submatrix directly above
                if (i > 0) {
                    grid[i][j] += grid[i - 1][j];
                }
                // Add the sum from the submatrix directly to the left
                if (j > 0) {
                    grid[i][j] += grid[i][j - 1];
                }
                // Subtract the overlapping top-left diagonal submatrix that got added twice
                if (i > 0 && j > 0) {
                    grid[i][j] -= grid[i - 1][j - 1];
                }
                
                // If the sum of the current submatrix (0,0) to (i,j) is within bounds, count it
                if (grid[i][j] <= k) {
                    count++;
                }
            }
        }
        
        return count;
    }
};