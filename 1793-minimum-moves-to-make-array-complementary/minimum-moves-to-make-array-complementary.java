class Solution {
    public int minMoves(int[] nums, int limit) {
        int n = nums.length;

        // Difference array
        int[] diff = new int[2 * limit + 2];

        for (int i = 0; i < n / 2; i++) {

            int a = nums[i];
            int b = nums[n - 1 - i];

            int low = Math.min(a, b) + 1;
            int high = Math.max(a, b) + limit;
            int sum = a + b;

            // Initially assume 2 moves for all sums
            diff[2] += 2;

            // From low to high => 1 move instead of 2
            diff[low] -= 1;
            diff[high + 1] += 1;

            // Exact sum => 0 moves instead of 1
            diff[sum] -= 1;
            diff[sum + 1] += 1;
        }

        int ans = Integer.MAX_VALUE;
        int curr = 0;

        for (int s = 2; s <= 2 * limit; s++) {
            curr += diff[s];
            ans = Math.min(ans, curr);
        }

        return ans;
    }
}