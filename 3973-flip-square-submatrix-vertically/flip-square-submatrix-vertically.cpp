class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        // Iterate through the top half of the submatrix's rows
        for (int i = 0; i < k / 2; ++i) {
            // Iterate through all columns of the submatrix
            for (int j = 0; j < k; ++j) {
                // Swap the current element with the corresponding element in the vertically opposite row
                swap(grid[x + i][y + j], grid[x + k - 1 - i][y + j]);
            }
        }
        
        return grid;
    }
};