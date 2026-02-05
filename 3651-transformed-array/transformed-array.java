class Solution {
    public int[] constructTransformedArray(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];

        for (int i = 0; i < n; i++) {
            if (nums[i] == 0) {
                result[i] = 0;
            } else {
                int newIndex = (i + nums[i]) % n;

                // Fix negative index due to Java modulo behavior
                if (newIndex < 0) {
                    newIndex += n;
                }

                result[i] = nums[newIndex];
            }
        }

        return result;
    }
}
