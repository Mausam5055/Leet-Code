class Solution {

    int[][] dirs = {{1,0},{-1,0},{0,1},{0,-1}};

    public List<List<Integer>> pacificAtlantic(int[][] heights) {

        int m = heights.length;
        int n = heights[0].length;

        boolean[][] pac = new boolean[m][n];
        boolean[][] atl = new boolean[m][n];

        // Pacific: top row + left column
        for (int i = 0; i < m; i++)
            dfs(heights, pac, i, 0);

        for (int j = 0; j < n; j++)
            dfs(heights, pac, 0, j);

        // Atlantic: bottom row + right column
        for (int i = 0; i < m; i++)
            dfs(heights, atl, i, n - 1);

        for (int j = 0; j < n; j++)
            dfs(heights, atl, m - 1, j);

        // Collect result
        List<List<Integer>> res = new ArrayList<>();

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (pac[i][j] && atl[i][j]) {
                    res.add(Arrays.asList(i, j));
                }
            }
        }

        return res;
    }

    void dfs(int[][] h, boolean[][] vis, int r, int c) {

        if (vis[r][c]) return;

        vis[r][c] = true;

        int m = h.length;
        int n = h[0].length;

        for (int[] d : dirs) {
            int nr = r + d[0];
            int nc = c + d[1];

            if (nr >= 0 && nr < m && nc >= 0 && nc < n
                && h[nr][nc] >= h[r][c]) {

                dfs(h, vis, nr, nc);
            }
        }
    }
}