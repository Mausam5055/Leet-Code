class Solution {
    public int numberOfSubmatrices(char[][] grid) {
        int n = grid.length;
        int m = grid[0].length;

        int[][] prefix = new int[n][m];
        int[][] countX = new int[n][m];

        int ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                int val = 0;
                if (grid[i][j] == 'X') val = 1;
                else if (grid[i][j] == 'Y') val = -1;

                int x = (grid[i][j] == 'X') ? 1 : 0;

                prefix[i][j] = val;
                countX[i][j] = x;

                if (i > 0) {
                    prefix[i][j] += prefix[i - 1][j];
                    countX[i][j] += countX[i - 1][j];
                }
                if (j > 0) {
                    prefix[i][j] += prefix[i][j - 1];
                    countX[i][j] += countX[i][j - 1];
                }
                if (i > 0 && j > 0) {
                    prefix[i][j] -= prefix[i - 1][j - 1];
                    countX[i][j] -= countX[i - 1][j - 1];
                }

                // Check condition
                if (prefix[i][j] == 0 && countX[i][j] > 0) {
                    ans++;
                }
            }
        }

        return ans;
    }
}