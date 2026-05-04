class Solution {
    public int countPartitions(int[] nums, int k) {
        int n = nums.length;
        int mod = 1_000_000_007;

        long[] dp = new long[n + 1];
        long[] prefix = new long[n + 1];

        dp[0] = 1;
        prefix[0] = 1;

        Deque<Integer> maxD = new ArrayDeque<>();
        Deque<Integer> minD = new ArrayDeque<>();

        int j = 0;

        for (int i = 0; i < n; i++) {
            // maintain max deque
            while (!maxD.isEmpty() && nums[maxD.peekLast()] <= nums[i]) {
                maxD.pollLast();
            }
            maxD.addLast(i);

            // maintain min deque
            while (!minD.isEmpty() && nums[minD.peekLast()] >= nums[i]) {
                minD.pollLast();
            }
            minD.addLast(i);

            // shrink window
            while (nums[maxD.peekFirst()] - nums[minD.peekFirst()] > k) {
                if (maxD.peekFirst() == j) maxD.pollFirst();
                if (minD.peekFirst() == j) minD.pollFirst();
                j++;
            }

            // dp transition
            dp[i + 1] = (prefix[i] - (j > 0 ? prefix[j - 1] : 0) + mod) % mod;

            // update prefix
            prefix[i + 1] = (prefix[i] + dp[i + 1]) % mod;
        }

        return (int) dp[n];
    }
}