class Solution {
    public boolean hasIncreasingSubarrays(List<Integer> nums, int k) {
        int n = nums.size();

        for (int a = 0; a <= n - 2 * k; a++) {

            boolean first = true;
            boolean second = true;

            // check first subarray
            for (int i = a; i < a + k - 1; i++) {
                if (nums.get(i) >= nums.get(i + 1)) {
                    first = false;
                    break;
                }
            }

            // check second subarray
            for (int i = a + k; i < a + 2 * k - 1; i++) {
                if (nums.get(i) >= nums.get(i + 1)) {
                    second = false;
                    break;
                }
            }

            if (first && second) return true;
        }

        return false;
    }
}