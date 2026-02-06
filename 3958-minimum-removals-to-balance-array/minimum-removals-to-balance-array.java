import java.util.Arrays;

class Solution {
    public int minRemoval(int[] nums, int k) {
        Arrays.sort(nums);
        int n = nums.length;
        
        int left = 0;
        int maxWindow = 1;  // at least one element is always balanced
        
        for (int right = 0; right < n; right++) {
            while ((long) nums[right] > (long) nums[left] * k) {
                left++;
            }
            maxWindow = Math.max(maxWindow, right - left + 1);
        }
        
        return n - maxWindow;
    }
}
