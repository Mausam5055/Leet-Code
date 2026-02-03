class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));

        int top = 0, bottom = n - 1;
        int left = 0, right = n - 1;
        int val = 1;

        while (top <= bottom && left <= right) {

            // 1. Left to Right (top row)
            for (int col = left; col <= right; col++) {
                matrix[top][col] = val++;
            }
            top++;

            // 2. Top to Bottom (right column)
            for (int row = top; row <= bottom; row++) {
                matrix[row][right] = val++;
            }
            right--;

            // 3. Right to Left (bottom row)
            for (int col = right; col >= left; col--) {
                matrix[bottom][col] = val++;
            }
            bottom--;

            // 4. Bottom to Top (left column)
            for (int row = bottom; row >= top; row--) {
                matrix[row][left] = val++;
            }
            left++;
        }

        return matrix;
    }
};
