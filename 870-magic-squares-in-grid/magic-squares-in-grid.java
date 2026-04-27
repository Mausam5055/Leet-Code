class Solution {
    public int numMagicSquaresInside(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int count = 0;
        
        for(int i = 0; i <= m - 3; i++) {
            for(int j = 0; j <= n - 3; j++) {
                if(isMagic(grid, i, j)) count++;
            }
        }
        
        return count;
    }
    
    private boolean isMagic(int[][] g, int i, int j) {
        // Step 1: center must be 5
        if(g[i+1][j+1] != 5) return false;
        
        // Step 2: check numbers 1-9 unique
        boolean[] seen = new boolean[10];
        
        for(int r = i; r < i + 3; r++) {
            for(int c = j; c < j + 3; c++) {
                int val = g[r][c];
                if(val < 1 || val > 9 || seen[val]) return false;
                seen[val] = true;
            }
        }
        
        // Step 3: check sums = 15
        int sum;
        
        // rows
        for(int r = i; r < i + 3; r++) {
            sum = g[r][j] + g[r][j+1] + g[r][j+2];
            if(sum != 15) return false;
        }
        
        // columns
        for(int c = j; c < j + 3; c++) {
            sum = g[i][c] + g[i+1][c] + g[i+2][c];
            if(sum != 15) return false;
        }
        
        // diagonals
        if(g[i][j] + g[i+1][j+1] + g[i+2][j+2] != 15) return false;
        if(g[i][j+2] + g[i+1][j+1] + g[i+2][j] != 15) return false;
        
        return true;
    }
}