import java.util.*;

class Solution {

    TreeMap<Integer, Integer> small = new TreeMap<>();
    TreeMap<Integer, Integer> large = new TreeMap<>();
    int smallSize = 0;
    long sumSmall = 0;
    int need;

    public long minimumCost(int[] nums, int k, int dist) {
        int n = nums.length;
        need = k - 1;

        int left = 1;
        long ans = Long.MAX_VALUE;

        for (int right = 1; right < n; right++) {
            add(nums[right]);

            while (right - left > dist) {
                remove(nums[left]);
                left++;
            }

            if (right - left + 1 >= need) {
                ans = Math.min(ans, sumSmall + nums[0]);
            }
        }

        return ans;
    }

    private void add(int x) {
        if (smallSize < need) {
            inc(small, x);
            smallSize++;
            sumSmall += x;
        } else if (!small.isEmpty() && x < small.lastKey()) {
            inc(small, x);
            sumSmall += x;
            smallSize++;

            int move = small.lastKey();
            dec(small, move);
            sumSmall -= move;
            smallSize--;

            inc(large, move);
        } else {
            inc(large, x);
        }
    }

    private void remove(int x) {
        if (small.containsKey(x)) {
            dec(small, x);
            smallSize--;
            sumSmall -= x;
        } else {
            dec(large, x);
        }
        rebalance();
    }

    private void rebalance() {
        while (smallSize > need) {
            int x = small.lastKey();
            dec(small, x);
            smallSize--;
            sumSmall -= x;
            inc(large, x);
        }
        while (smallSize < need && !large.isEmpty()) {
            int x = large.firstKey();
            dec(large, x);
            inc(small, x);
            smallSize++;
            sumSmall += x;
        }
    }

    private void inc(TreeMap<Integer, Integer> map, int x) {
        map.put(x, map.getOrDefault(x, 0) + 1);
    }

    private void dec(TreeMap<Integer, Integer> map, int x) {
        int cnt = map.get(x);
        if (cnt == 1) map.remove(x);
        else map.put(x, cnt - 1);
    }
}
