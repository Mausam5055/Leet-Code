class Solution {
    int m, n;
    boolean[][] visited;
    
    public boolean containsCycle(char[][] grid) {
        m = grid.length;
        n = grid[0].length;
        visited = new boolean[m][n];
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (!visited[i][j]) {
                    if (dfs(grid, i, j, -1, -1)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    private boolean dfs(char[][] grid, int x, int y, int px, int py) {
        visited[x][y] = true;
        
        int[] dx = {1, -1, 0, 0};
        int[] dy = {0, 0, 1, -1};
        
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            
            if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
            if (grid[nx][ny] != grid[x][y]) continue;
            
            // if already visited and not coming from parent → cycle
            if (visited[nx][ny]) {
                if (nx != px || ny != py) {
                    return true;
                }
            } else {
                if (dfs(grid, nx, ny, x, y)) {
                    return true;
                }
            }
        }
        return false;
    }
}