class Solution {
    public int[] getSneakyNumbers(int[] nums) {
        int n = nums.length;
        int[] freq = new int[101]; // since nums[i] <= 100
        int[] ans = new int[2];
        int idx = 0;

        for (int num : nums) {
            freq[num]++;
        }

        for (int i = 0; i < freq.length; i++) {
            if (freq[i] == 2) {
                ans[idx++] = i;
            }
        }

        return ans;
    }
}