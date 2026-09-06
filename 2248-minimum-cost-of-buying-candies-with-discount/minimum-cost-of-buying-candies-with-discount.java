import java.util.Arrays;

class Solution {
    public int minimumCost(int[] cost) {
        // Sort the array in ascending order
        Arrays.sort(cost);
        
        int totalCost = 0;
        int n = cost.length;
        
        // Iterate backwards from the most expensive candy
        for (int i = n - 1; i >= 0; i--) {
            // We pay for the 1st and 2nd candies in every group of 3
            // The 3rd candy (where (n - i) is a multiple of 3) is free
            if ((n - i) % 3 != 0) {
                totalCost += cost[i];
            }
        }
        
        return totalCost;
    }
}