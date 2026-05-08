class Solution {

    public int minJumps(int[] nums) {

        int n = nums.length;
        if (n == 1) return 0;

        int max = 0;
        for (int x : nums) max = Math.max(max, x);

        // SPF sieve
        int[] spf = new int[max + 1];

        for (int i = 2; i <= max; i++) {
            if (spf[i] == 0) {
                spf[i] = i;

                if ((long) i * i <= max) {
                    for (int j = i * i; j <= max; j += i) {
                        if (spf[j] == 0) {
                            spf[j] = i;
                        }
                    }
                }
            }
        }

        // prime -> indices divisible by prime
        Map<Integer, List<Integer>> map = new HashMap<>();

        for (int i = 0; i < n; i++) {

            int x = nums[i];

            while (x > 1) {

                int p = spf[x];

                map.computeIfAbsent(p, k -> new ArrayList<>()).add(i);

                while (x % p == 0) x /= p;
            }
        }

        ArrayDeque<Integer> q = new ArrayDeque<>();

        boolean[] vis = new boolean[n];
        vis[0] = true;

        Set<Integer> usedPrime = new HashSet<>();

        q.offer(0);

        int steps = 0;

        while (!q.isEmpty()) {

            int size = q.size();

            while (size-- > 0) {

                int idx = q.poll();

                if (idx == n - 1) return steps;

                // left
                if (idx - 1 >= 0 && !vis[idx - 1]) {
                    vis[idx - 1] = true;
                    q.offer(idx - 1);
                }

                // right
                if (idx + 1 < n && !vis[idx + 1]) {
                    vis[idx + 1] = true;
                    q.offer(idx + 1);
                }

                int val = nums[idx];

                // check prime
                if (val > 1 && spf[val] == val && !usedPrime.contains(val)) {

                    usedPrime.add(val);

                    List<Integer> next = map.get(val);

                    if (next != null) {

                        for (int ni : next) {

                            if (!vis[ni]) {
                                vis[ni] = true;
                                q.offer(ni);
                            }
                        }
                    }
                }
            }

            steps++;
        }

        return -1;
    }
}