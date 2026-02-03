import java.util.*;

class Solution {
    public int minCost(int[][] grid, int k) {
        int m = grid.length, n = grid[0].length;
        int INF = Integer.MAX_VALUE / 2;

        int[][][] dist = new int[m][n][k + 1];
        for (int[][] layer : dist)
            for (int[] row : layer)
                Arrays.fill(row, INF);

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        dist[0][0][0] = 0;
        pq.offer(new int[]{0, 0, 0, 0}); // cost, i, j, teleportsUsed

        // Sort cells by value
        List<int[]> cells = new ArrayList<>();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                cells.add(new int[]{grid[i][j], i, j});
        cells.sort(Comparator.comparingInt(a -> a[0]));

        // For each teleport count, how many cells have been unlocked
        int[] unlockedPtr = new int[k + 1];

        while (!pq.isEmpty()) {
            int[] cur = pq.poll();
            int cost = cur[0], i = cur[1], j = cur[2], t = cur[3];

            if (cost > dist[i][j][t]) continue;
            if (i == m - 1 && j == n - 1) return cost;

            // Normal moves
            if (i + 1 < m) {
                int newCost = cost + grid[i + 1][j];
                if (newCost < dist[i + 1][j][t]) {
                    dist[i + 1][j][t] = newCost;
                    pq.offer(new int[]{newCost, i + 1, j, t});
                }
            }
            if (j + 1 < n) {
                int newCost = cost + grid[i][j + 1];
                if (newCost < dist[i][j + 1][t]) {
                    dist[i][j + 1][t] = newCost;
                    pq.offer(new int[]{newCost, i, j + 1, t});
                }
            }

            // Teleport transitions
            if (t < k) {
                int ptr = unlockedPtr[t + 1];
                while (ptr < cells.size() && cells.get(ptr)[0] <= grid[i][j]) {
                    int x = cells.get(ptr)[1];
                    int y = cells.get(ptr)[2];

                    if (cost < dist[x][y][t + 1]) {
                        dist[x][y][t + 1] = cost;
                        pq.offer(new int[]{cost, x, y, t + 1});
                    }
                    ptr++;
                }
                unlockedPtr[t + 1] = ptr; // save progress
            }
        }

        return -1;
    }
}
