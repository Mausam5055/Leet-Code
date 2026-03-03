import java.util.*;

class Solution {
    public int swimInWater(int[][] grid) {
        int n = grid.length;
        
        boolean[][] visited = new boolean[n][n];
        PriorityQueue<int[]> pq = new PriorityQueue<>(
            (a, b) -> a[0] - b[0]
        );
        
        // {time, row, col}
        pq.offer(new int[]{grid[0][0], 0, 0});
        
        int[][] directions = {{1,0},{-1,0},{0,1},{0,-1}};
        
        while (!pq.isEmpty()) {
            int[] current = pq.poll();
            int time = current[0];
            int r = current[1];
            int c = current[2];
            
            if (r == n-1 && c == n-1)
                return time;
            
            if (visited[r][c]) continue;
            visited[r][c] = true;
            
            for (int[] d : directions) {
                int nr = r + d[0];
                int nc = c + d[1];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                    pq.offer(new int[]{
                        Math.max(time, grid[nr][nc]),
                        nr,
                        nc
                    });
                }
            }
        }
        
        return -1; // should never reach
    }
}