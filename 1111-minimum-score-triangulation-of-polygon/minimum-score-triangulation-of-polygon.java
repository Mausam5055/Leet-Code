class Solution {
    public int minScoreTriangulation(int[] values) {
        int n = values.length;
        // dp[i][j] will store the minimum score to triangulate the polygon from vertex i to j
        int[][] dp = new int[n][n];

        // We check shapes of increasing lengths. 
        // len is the distance between the start vertex i and end vertex j.
        // It starts at 2 because you need at least 3 points (distance of 2) to form a triangle.
        for (int len = 2; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                dp[i][j] = Integer.MAX_VALUE;
                
                // Try every possible middle vertex k to form a triangle (i, k, j)
                for (int k = i + 1; k < j; k++) {
                    // Score = (triangle i,k,j) + (left sub-polygon) + (right sub-polygon)
                    int currentScore = values[i] * values[k] * values[j] + dp[i][k] + dp[k][j];
                    
                    // Keep the smallest score we find
                    dp[i][j] = Math.min(dp[i][j], currentScore);
                }
            }
        }
        
        // The answer is the min score to triangulate from the first to the last vertex
        return dp[0][n - 1];
    }
}