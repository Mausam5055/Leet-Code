class Solution {
    public boolean areSimilar(int[][] mat, int k) {
        int m = mat.length;
        int n = mat[0].length;

        // Reduce unnecessary shifts
        k = k % n;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int newCol;

                if (i % 2 == 0) {
                    // even row → left shift
                    newCol = (j + k) % n;
                } else {
                    // odd row → right shift
                    newCol = (j - k + n) % n;
                }

                // Check if after shift it's same
                if (mat[i][j] != mat[i][newCol]) {
                    return false;
                }
            }
        }

        return true;
    }
}