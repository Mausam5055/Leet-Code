class Solution {
    public boolean isTrionic(int[] nums) {
        int n = nums.length;
        int i = 0;

        // Phase 1: strictly increasing
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            i++;
        }
        if (i == 0) return false; // no increasing part

        // Phase 2: strictly decreasing
        int p = i;
        while (i + 1 < n && nums[i] > nums[i + 1]) {
            i++;
        }
        if (i == p) return false; // no decreasing part

        // Phase 3: strictly increasing again
        int q = i;
        while (i + 1 < n && nums[i] < nums[i + 1]) {
            i++;
        }

        // Must reach end and have all 3 parts
        return i == n - 1 && q < n - 1;
    }
}
