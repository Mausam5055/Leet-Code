class Solution {
    public long maxProfit(int[] prices, int[] strategy, int k) {

        int n = prices.length;

        long base = 0;

        for (int i = 0; i < n; i++) {
            base += 1L * strategy[i] * prices[i];
        }

        int half = k / 2;

        // gain if changed to 0
        long[] gain0 = new long[n];

        // gain if changed to 1
        long[] gain1 = new long[n];

        for (int i = 0; i < n; i++) {

            gain0[i] = 1L * (0 - strategy[i]) * prices[i];

            gain1[i] = 1L * (1 - strategy[i]) * prices[i];
        }

        // prefix sums
        long[] pref0 = new long[n + 1];
        long[] pref1 = new long[n + 1];

        for (int i = 0; i < n; i++) {
            pref0[i + 1] = pref0[i] + gain0[i];
            pref1[i + 1] = pref1[i] + gain1[i];
        }

        long ans = base;

        for (int start = 0; start <= n - k; start++) {

            int mid = start + half;
            int end = start + k;

            // first half -> 0
            long leftGain = pref0[mid] - pref0[start];

            // second half -> 1
            long rightGain = pref1[end] - pref1[mid];

            ans = Math.max(ans, base + leftGain + rightGain);
        }

        return ans;
    }
}