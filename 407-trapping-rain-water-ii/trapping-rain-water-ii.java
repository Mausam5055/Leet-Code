import java.util.*;

class Solution {
    public int trapRainWater(int[][] heightMap) {

        int m = heightMap.length;
        int n = heightMap[0].length;

        if (m < 3 || n < 3) return 0;

        boolean[][] visited = new boolean[m][n];
        PriorityQueue<int[]> pq =
                new PriorityQueue<>((a, b) -> a[0] - b[0]);

        // Add all boundary cells
        for (int i = 0; i < m; i++) {
            pq.offer(new int[]{heightMap[i][0], i, 0});
            pq.offer(new int[]{heightMap[i][n - 1], i, n - 1});
            visited[i][0] = visited[i][n - 1] = true;
        }

        for (int j = 1; j < n - 1; j++) {
            pq.offer(new int[]{heightMap[0][j], 0, j});
            pq.offer(new int[]{heightMap[m - 1][j], m - 1, j});
            visited[0][j] = visited[m - 1][j] = true;
        }

        int water = 0;

        int[][] dirs = {{1,0},{-1,0},{0,1},{0,-1}};

        while (!pq.isEmpty()) {

            int[] cur = pq.poll();
            int h = cur[0];
            int x = cur[1];
            int y = cur[2];

            for (int[] d : dirs) {

                int nx = x + d[0];
                int ny = y + d[1];

                if (nx < 0 || ny < 0 || nx >= m || ny >= n || visited[nx][ny])
                    continue;

                visited[nx][ny] = true;

                int nh = heightMap[nx][ny];

                // water trapped
                if (h > nh) {
                    water += h - nh;
                }

                // push with updated boundary height
                pq.offer(new int[]{Math.max(h, nh), nx, ny});
            }
        }

        return water;
    }
}