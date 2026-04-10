class Solution {
    public int minOperations(int[] nums) {
        int n = nums.length;

        // Step 1: count number of 1s
        int countOnes = 0;
        for (int num : nums) {
            if (num == 1) countOnes++;
        }

        // Case 1: already has 1
        if (countOnes > 0) {
            return n - countOnes;
        }

        // Case 2: find smallest subarray with gcd = 1
        int minLen = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            int g = nums[i];

            for (int j = i; j < n; j++) {
                g = gcd(g, nums[j]);

                if (g == 1) {
                    minLen = Math.min(minLen, j - i + 1);
                    break; // no need to extend further
                }
            }
        }

        // If no subarray found
        if (minLen == Integer.MAX_VALUE) {
            return -1;
        }

        // total operations
        return (minLen - 1) + (n - 1);
    }

    private int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}