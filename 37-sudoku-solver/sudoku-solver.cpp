class Solution {
public:
    bool row[9][10] = {}, col[9][10] = {}, box[9][10] = {};

    bool solve(vector<vector<char>>& board, int cell) {
        if (cell == 81) return true;  // solved all cells

        int r = cell / 9;
        int c = cell % 9;

        if (board[r][c] != '.')
            return solve(board, cell + 1);

        int b = (r / 3) * 3 + (c / 3);

        for (int d = 1; d <= 9; d++) {
            if (!row[r][d] && !col[c][d] && !box[b][d]) {
                board[r][c] = d + '0';
                row[r][d] = col[c][d] = box[b][d] = true;

                if (solve(board, cell + 1)) return true;

                // backtrack
                board[r][c] = '.';
                row[r][d] = col[c][d] = box[b][d] = false;
            }
        }
        return false;
    }

    void solveSudoku(vector<vector<char>>& board) {
        // initialize constraints
        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] != '.') {
                    int d = board[r][c] - '0';
                    int b = (r / 3) * 3 + (c / 3);
                    row[r][d] = col[c][d] = box[b][d] = true;
                }
            }
        }
        solve(board, 0);
    }
};
