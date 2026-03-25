class Solution {
    public boolean canPartitionGrid(int[][] grid) {
        int m = grid.length, n = grid[0].length;

        long total = 0;

        // total sum
        for (int[] row : grid) {
            for (int val : row) {
                total += val;
            }
        }

        // if odd → impossible
        if (total % 2 != 0) return false;

        long target = total / 2;

        // 🔹 Horizontal cut
        long sum = 0;
        for (int i = 0; i < m - 1; i++) {
            for (int j = 0; j < n; j++) {
                sum += grid[i][j];
            }
            if (sum == target) return true;
        }

        // 🔹 Vertical cut
        sum = 0;
        for (int j = 0; j < n - 1; j++) {
            for (int i = 0; i < m; i++) {
                sum += grid[i][j];
            }
            if (sum == target) return true;
        }

        return false;
    }
}