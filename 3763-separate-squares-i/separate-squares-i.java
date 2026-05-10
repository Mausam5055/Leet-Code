class Solution {
    
    public double separateSquares(int[][] squares) {
        double total = 0;
        double low = Double.MAX_VALUE;
        double high = 0;
        
        // total area + search boundaries
        for (int[] s : squares) {
            int y = s[1];
            int l = s[2];
            
            total += 1.0 * l * l;
            low = Math.min(low, y);
            high = Math.max(high, y + l);
        }
        
        // binary search
        for (int iter = 0; iter < 100; iter++) {
            double mid = (low + high) / 2.0;
            
            double below = 0;
            
            for (int[] s : squares) {
                double y = s[1];
                double l = s[2];
                
                if (mid <= y) {
                    // nothing below
                    continue;
                } 
                else if (mid >= y + l) {
                    // full square below
                    below += l * l;
                } 
                else {
                    // partially below
                    below += (mid - y) * l;
                }
            }
            
            if (below * 2 >= total) {
                high = mid;
            } else {
                low = mid;
            }
        }
        
        return low;
    }
}