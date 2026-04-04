import java.util.*;

class Solution {
    public long maxPower(int[] stations, int r, int k) {
        int n = stations.length;

        long[] prefix = new long[n + 1];
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stations[i];
        }

        // initial power array
        long[] power = new long[n];
        for (int i = 0; i < n; i++) {
            int left = Math.max(0, i - r);
            int right = Math.min(n - 1, i + r);
            power[i] = prefix[right + 1] - prefix[left];
        }

        long low = 0, high = (long) 1e14;

        while (low < high) {
            long mid = (low + high + 1) / 2;

            if (canAchieve(power, r, k, mid)) {
                low = mid;
            } else {
                high = mid - 1;
            }
        }

        return low;
    }

    private boolean canAchieve(long[] power, int r, int k, long target) {
        int n = power.length;
        long[] extra = new long[n];
        long used = 0, added = 0;

        for (int i = 0; i < n; i++) {
            if (i > r) {
                added -= extra[i - r - 1];
            }

            long curr = power[i] + added;

            if (curr < target) {
                long need = target - curr;
                used += need;
                if (used > k) return false;

                added += need;

                int pos = Math.min(n - 1, i + r);
                extra[pos] += need;
            }
        }

        return true;
    }
}