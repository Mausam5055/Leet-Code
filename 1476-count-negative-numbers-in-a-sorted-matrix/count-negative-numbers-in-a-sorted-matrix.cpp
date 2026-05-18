class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {

        int m = grid.size();
        int n = grid[0].size();

        int row = m - 1;
        int col = 0;

        int count = 0;

        while (row >= 0 && col < n) {

            // Negative found
            if (grid[row][col] < 0) {

                // Count all remaining elements in row
                count += (n - col);

                // Move upward
                row--;
            }
            else {

                // Move right
                col++;
            }
        }

        return count;
    }
};