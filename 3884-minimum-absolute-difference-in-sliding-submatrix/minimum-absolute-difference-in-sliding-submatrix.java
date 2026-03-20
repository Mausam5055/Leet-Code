import java.util.*;

class Solution {
    public int[][] minAbsDiff(int[][] grid, int k) {
        int m = grid.length;
        int n = grid[0].length;
        
        int[][] ans = new int[m - k + 1][n - k + 1];
        
        for (int i = 0; i <= m - k; i++) {
            for (int j = 0; j <= n - k; j++) {
                
                Set<Integer> set = new HashSet<>();
                
                // collect unique elements
                for (int x = i; x < i + k; x++) {
                    for (int y = j; y < j + k; y++) {
                        set.add(grid[x][y]);
                    }
                }
                
                List<Integer> list = new ArrayList<>(set);
                Collections.sort(list);
                
                int minDiff = Integer.MAX_VALUE;
                
                for (int t = 1; t < list.size(); t++) {
                    minDiff = Math.min(minDiff, 
                        list.get(t) - list.get(t - 1));
                }
                
                ans[i][j] = (list.size() <= 1) ? 0 : minDiff;
            }
        }
        
        return ans;
    }
}