import java.util.Arrays;

class Solution {
    public long minimumCost(String source, String target, char[] original, char[] changed, int[] cost) {
        // Initialize a 26x26 matrix to store minimum costs between characters
        // We use a large enough constant for Infinity, but safe from overflow during addition
        long[][] dist = new long[26][26];
        long INF = Integer.MAX_VALUE; // Safe upper bound since max individual path cost is ~26 * 10^6
        
        for (long[] row : dist) {
            Arrays.fill(row, INF);
        }
        
        // Distance to self is always 0
        for (int i = 0; i < 26; i++) {
            dist[i][i] = 0;
        }
        
        // 1. Build the initial graph from the input arrays
        for (int i = 0; i < original.length; i++) {
            int u = original[i] - 'a';
            int v = changed[i] - 'a';
            // There might be multiple edges between same characters, keep the minimum
            dist[u][v] = Math.min(dist[u][v], cost[i]);
        }
        
        // 2. Apply Floyd-Warshall Algorithm to find all-pairs shortest paths
        // O(26^3) - Constant time complexity relative to string length
        for (int k = 0; k < 26; k++) {
            for (int i = 0; i < 26; i++) {
                for (int j = 0; j < 26; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        
        // 3. Calculate total cost for the string conversion
        long totalCost = 0;
        int n = source.length();
        
        for (int i = 0; i < n; i++) {
            int u = source.charAt(i) - 'a';
            int v = target.charAt(i) - 'a';
            
            if (u != v) {
                if (dist[u][v] == INF) {
                    return -1; // Conversion impossible
                }
                totalCost += dist[u][v];
            }
        }
        
        return totalCost;
    }
}