class Solution {
public:
    vector<vector<string>> result;
    vector<string> board;
    vector<bool> cols, diag1, diag2;
    int n;

    void backtrack(int row) {
        // base case: all queens placed
        if (row == n) {
            result.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (cols[col] || diag1[row - col + n - 1] || diag2[row + col])
                continue;

            // place queen
            board[row][col] = 'Q';
            cols[col] = diag1[row - col + n - 1] = diag2[row + col] = true;

            backtrack(row + 1);

            // remove queen (backtrack)
            board[row][col] = '.';
            cols[col] = diag1[row - col + n - 1] = diag2[row + col] = false;
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        this->n = n;
        board = vector<string>(n, string(n, '.'));
        cols = vector<bool>(n, false);
        diag1 = vector<bool>(2 * n - 1, false);
        diag2 = vector<bool>(2 * n - 1, false);

        backtrack(0);
        return result;
    }
};
