class Solution {
    public long getDescentPeriods(int[] prices) {
        long result = 0;
        long len = 1;  // every single element counts
        
        result = 1;
        
        for (int i = 1; i < prices.length; i++) {
            if (prices[i] == prices[i - 1] - 1) {
                len++;
            } else {
                len = 1;
            }
            result += len;
        }
        
        return result;
    }
}