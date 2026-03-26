class Solution {
    // FIXED: Changed method name from canPartition to canPartitionGrid
    public boolean canPartitionGrid(int[][] grid) {
        return checkHorizontal(grid) || checkVertical(grid);
    }

    private boolean checkHorizontal(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        if (m == 1) return false; // Can't make a horizontal cut

        long[] rowSum = new long[m];
        long totalSum = 0;
        int[] freqTop = new int[100005];
        int[] freqBot = new int[100005];

        // Initialize sums and the bottom frequency array (initially all elements)
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                rowSum[i] += grid[i][j];
                totalSum += grid[i][j];
                if (grid[i][j] <= 100000) {
                    freqBot[grid[i][j]]++;
                }
            }
        }

        long topSum = 0;
        // Sweep horizontal cuts (after row k)
        for (int k = 0; k < m - 1; k++) {
            topSum += rowSum[k];
            long botSum = totalSum - topSum;

            // Move current row elements from bottom to top section
            for (int j = 0; j < n; j++) {
                int val = grid[k][j];
                if (val <= 100000) {
                    freqBot[val]--;
                    freqTop[val]++;
                }
            }

            long diff = Math.abs(topSum - botSum);
            if (diff == 0) return true;
            
            // Check if we can discount the difference
            if (diff <= 100000) {
                int D = (int) diff;
                if (topSum > botSum) {
                    // Larger sum is on top, look for D in top section
                    if (n == 1) {
                        if (grid[0][0] == D || grid[k][0] == D) return true;
                    } else if (k == 0) { // Top is a 1D row
                        if (grid[0][0] == D || grid[0][n - 1] == D) return true;
                    } else { // Top is 2D
                        if (freqTop[D] > 0) return true;
                    }
                } else {
                    // Larger sum is on bottom, look for D in bottom section
                    if (n == 1) {
                        if (grid[k + 1][0] == D || grid[m - 1][0] == D) return true;
                    } else if (m - 1 - k == 1) { // Bottom is a 1D row
                        if (grid[m - 1][0] == D || grid[m - 1][n - 1] == D) return true;
                    } else { // Bottom is 2D
                        if (freqBot[D] > 0) return true;
                    }
                }
            }
        }
        return false;
    }

    private boolean checkVertical(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        if (n == 1) return false; // Can't make a vertical cut

        long[] colSum = new long[n];
        long totalSum = 0;
        int[] freqLeft = new int[100005];
        int[] freqRight = new int[100005];

        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                colSum[j] += grid[i][j];
                totalSum += grid[i][j];
                if (grid[i][j] <= 100000) {
                    freqRight[grid[i][j]]++;
                }
            }
        }

        long leftSum = 0;
        // Sweep vertical cuts (after column c)
        for (int c = 0; c < n - 1; c++) {
            leftSum += colSum[c];
            long rightSum = totalSum - leftSum;

            // Move current col elements from right to left section
            for (int i = 0; i < m; i++) {
                int val = grid[i][c];
                if (val <= 100000) {
                    freqRight[val]--;
                    freqLeft[val]++;
                }
            }

            long diff = Math.abs(leftSum - rightSum);
            if (diff == 0) return true;

            if (diff <= 100000) {
                int D = (int) diff;
                if (leftSum > rightSum) {
                    if (m == 1) {
                        if (grid[0][0] == D || grid[0][c] == D) return true;
                    } else if (c == 0) { // Left is a 1D column
                        if (grid[0][0] == D || grid[m - 1][0] == D) return true;
                    } else { // Left is 2D
                        if (freqLeft[D] > 0) return true;
                    }
                } else {
                    if (m == 1) {
                        if (grid[0][c + 1] == D || grid[0][n - 1] == D) return true;
                    } else if (n - 1 - c == 1) { // Right is a 1D column
                        if (grid[0][n - 1] == D || grid[m - 1][n - 1] == D) return true;
                    } else { // Right is 2D
                        if (freqRight[D] > 0) return true;
                    }
                }
            }
        }
        return false;
    }
}