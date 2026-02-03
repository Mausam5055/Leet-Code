class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> result;
        if (matrix.empty()) return result;

        int top = 0;
        int bottom = matrix.size() - 1;
        int left = 0;
        int right = matrix[0].size() - 1;

        while (top <= bottom && left <= right) {

            // 1. Traverse top row (left → right)
            for (int col = left; col <= right; col++)
                result.push_back(matrix[top][col]);
            top++;

            // 2. Traverse right column (top → bottom)
            for (int row = top; row <= bottom; row++)
                result.push_back(matrix[row][right]);
            right--;

            // 3. Traverse bottom row (right → left)
            if (top <= bottom) {
                for (int col = right; col >= left; col--)
                    result.push_back(matrix[bottom][col]);
                bottom--;
            }

            // 4. Traverse left column (bottom → top)
            if (left <= right) {
                for (int row = bottom; row >= top; row--)
                    result.push_back(matrix[row][left]);
                left++;
            }
        }

        return result;
    }
};
