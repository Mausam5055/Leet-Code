import java.util.*;

class Solution {
    private static final long INF = (long) 1e18;

    public long minimumCost(String source, String target, String[] original, String[] changed, int[] cost) {
        int n = source.length();

        // Group transformations by string length
        Map<Integer, Map<String, Integer>> idMapByLen = new HashMap<>();
        Map<Integer, long[][]> distByLen = new HashMap<>();

        // Step 1: Assign IDs to strings per length
        for (int i = 0; i < original.length; i++) {
            int len = original[i].length();
            idMapByLen.putIfAbsent(len, new HashMap<>());
            Map<String, Integer> idMap = idMapByLen.get(len);

            idMap.putIfAbsent(original[i], idMap.size());
            idMap.putIfAbsent(changed[i], idMap.size());
        }

        // Step 2: Build distance matrices
        for (int len : idMapByLen.keySet()) {
            int size = idMapByLen.get(len).size();
            long[][] dist = new long[size][size];

            for (int i = 0; i < size; i++) {
                Arrays.fill(dist[i], INF);
                dist[i][i] = 0;
            }

            distByLen.put(len, dist);
        }

        // Step 3: Fill direct edges
        for (int i = 0; i < original.length; i++) {
            int len = original[i].length();
            Map<String, Integer> idMap = idMapByLen.get(len);
            long[][] dist = distByLen.get(len);

            int u = idMap.get(original[i]);
            int v = idMap.get(changed[i]);
            dist[u][v] = Math.min(dist[u][v], cost[i]);
        }

        // Step 4: Floyd–Warshall per length
        for (int len : distByLen.keySet()) {
            long[][] dist = distByLen.get(len);
            int size = dist.length;

            for (int k = 0; k < size; k++) {
                for (int i = 0; i < size; i++) {
                    for (int j = 0; j < size; j++) {
                        if (dist[i][k] < INF && dist[k][j] < INF) {
                            dist[i][j] = Math.min(dist[i][j], dist[i][k] + dist[k][j]);
                        }
                    }
                }
            }
        }

        // Step 5: DP
        long[] dp = new long[n + 1];
        Arrays.fill(dp, INF);
        dp[n] = 0;

        for (int i = n - 1; i >= 0; i--) {

            // Case 1: characters already equal
            if (source.charAt(i) == target.charAt(i)) {
                dp[i] = dp[i + 1];
            }

            // Case 2: try all substring lengths
            for (int len : idMapByLen.keySet()) {
                if (i + len > n) continue;

                String subS = source.substring(i, i + len);
                String subT = target.substring(i, i + len);

                Map<String, Integer> idMap = idMapByLen.get(len);
                if (!idMap.containsKey(subS) || !idMap.containsKey(subT)) continue;

                long[][] dist = distByLen.get(len);
                long c = dist[idMap.get(subS)][idMap.get(subT)];

                if (c < INF && dp[i + len] < INF) {
                    dp[i] = Math.min(dp[i], c + dp[i + len]);
                }
            }
        }

        return dp[0] >= INF ? -1 : dp[0];
    }
}
