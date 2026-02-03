class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (dfs(board, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }

private:
    bool dfs(vector<vector<char>>& board, string& word, int i, int j, int index) {
        // Base case: all characters matched
        if (index == word.length()) return true;

        // Boundary & mismatch checks
        if (i < 0 || j < 0 || 
            i >= board.size() || j >= board[0].size() ||
            board[i][j] != word[index]) {
            return false;
        }

        // Mark as visited
        char temp = board[i][j];
        board[i][j] = '#';

        // Explore all 4 directions
        bool found =
            dfs(board, word, i + 1, j, index + 1) ||
            dfs(board, word, i - 1, j, index + 1) ||
            dfs(board, word, i, j + 1, index + 1) ||
            dfs(board, word, i, j - 1, index + 1);

        // Backtrack
        board[i][j] = temp;

        return found;
    }
};
