class Solution {
    public int maxSideLength(int[][] mat, int threshold) {
        int m = mat.length, n = mat[0].length;
        
        // Step 1: prefix sum
        int[][] prefix = new int[m + 1][n + 1];
        
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                prefix[i][j] = mat[i-1][j-1]
                             + prefix[i-1][j]
                             + prefix[i][j-1]
                             - prefix[i-1][j-1];
            }
        }
        
        int left = 0, right = Math.min(m, n);
        
        while(left < right) {
            int mid = (left + right + 1) / 2;
            
            if(isValid(prefix, mid, threshold, m, n)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        
        return left;
    }
    
    private boolean isValid(int[][] prefix, int len, int threshold, int m, int n) {
        for(int i = len; i <= m; i++) {
            for(int j = len; j <= n; j++) {
                int sum = prefix[i][j]
                        - prefix[i-len][j]
                        - prefix[i][j-len]
                        + prefix[i-len][j-len];
                
                if(sum <= threshold) return true;
            }
        }
        return false;
    }
}