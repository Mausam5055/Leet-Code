class Solution {
    public long minOperations(int[][] queries) {
        long[] pow4 = new long[32];
        pow4[0] = 1;
        for (int i = 1; i < 32; i++) {
            pow4[i] = pow4[i - 1] * 4;
            if (pow4[i] > 1_000_000_000L) break;
        }

        long totalOps = 0;

        for (int[] q : queries) {
            long l = q[0], r = q[1];
            long stepsSum = 0;

            for (int k = 1; k < 32; k++) {
                long start = pow4[k - 1];
                long end = pow4[k] - 1;

                if (start > r) break;

                long left = Math.max(l, start);
                long right = Math.min(r, end);

                if (left <= right) {
                    long count = right - left + 1;
                    stepsSum += count * k;
                }
            }

            totalOps += (stepsSum + 1) / 2; // ceil
        }

        return totalOps;
    }
}
