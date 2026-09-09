class Solution {
    public int missingMultiple(int[] nums, int k) {
        boolean[] present = new boolean[101];
        
        // Mark all numbers present in the array
        for (int num : nums) {
            if (num <= 100) {
                present[num] = true;
            }
        }
        
        int multiple = k;
        
        // Find the first multiple of k that is not marked as present
        while (multiple <= 100 && present[multiple]) {
            multiple += k;
        }
        
        return multiple;
    }
}