class Solution {
    fun solve(board: Array<CharArray>) {
        if (board.isEmpty()) return

        val m = board.size
        val n = board[0].size

        // DFS from boundary O's
        for (i in 0 until m) {
            if (board[i][0] == 'O') dfs(board, i, 0)
            if (board[i][n - 1] == 'O') dfs(board, i, n - 1)
        }

        for (j in 0 until n) {
            if (board[0][j] == 'O') dfs(board, 0, j)
            if (board[m - 1][j] == 'O') dfs(board, m - 1, j)
        }

        // Final conversion
        for (i in 0 until m) {
            for (j in 0 until n) {
                if (board[i][j] == 'O') board[i][j] = 'X'
                else if (board[i][j] == '#') board[i][j] = 'O'
            }
        }
    }

    private fun dfs(board: Array<CharArray>, i: Int, j: Int) {
        if (i < 0 || j < 0 || i >= board.size || j >= board[0].size)
            return
        if (board[i][j] != 'O') return

        board[i][j] = '#'

        dfs(board, i + 1, j)
        dfs(board, i - 1, j)
        dfs(board, i, j + 1)
        dfs(board, i, j - 1)
    }
}
