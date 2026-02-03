class Solution {
public:
    int count = 0;
    vector<bool> cols, diag1, diag2;
    int n;

    void backtrack(int row) {
        if (row == n) {
            count++;        // found a valid arrangement
            return;
        }

        for (int col = 0; col < n; col++) {
            if (cols[col] || diag1[row - col + n - 1] || diag2[row + col])
                continue;

            // place queen
            cols[col] = diag1[row - col + n - 1] = diag2[row + col] = true;

            backtrack(row + 1);

            // remove queen
            cols[col] = diag1[row - col + n - 1] = diag2[row + col] = false;
        }
    }

    int totalNQueens(int n) {
        this->n = n;
        cols = vector<bool>(n, false);
        diag1 = vector<bool>(2 * n - 1, false);
        diag2 = vector<bool>(2 * n - 1, false);

        backtrack(0);
        return count;
    }
};
