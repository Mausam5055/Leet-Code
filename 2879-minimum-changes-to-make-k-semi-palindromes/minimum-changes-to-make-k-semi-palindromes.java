class Solution {

    private int segmentCost(char[] s, int l, int m, List<Integer>[] factors) {
        int best = m;
        for (int d : factors[m]) {
            int groups = m / d; // Each group contains groups characters
            int changes = 0;
            for (int offset = 0; offset < d; offset++) {
                for (int t = 0; t < groups / 2; t++) {
                    // Pair characters from opposite ends of the group
                    if (
                        s[l + offset + t * d] !=
                        s[l + offset + (groups - 1 - t) * d]
                    ) {
                        changes++;
                    }
                }
            }
            best = Math.min(best, changes);
        }
        return best;
    }

    private int solve(int seg, int start, int n, int[][] cost, int[][] memo) {
        if (seg == 1) {
            // Only one segment remains
            return cost[start][n - 1];
        }
        if (memo[seg][start] != -1) {
            // Already computed
            return memo[seg][start];
        }
        int best = n;
        int limit = n - 1 - 2 * (seg - 1); // Leave room for seg-1 segments after the first segment
        for (int e = start + 1; e <= limit; e++) {
            best = Math.min(
                best,
                cost[start][e] + solve(seg - 1, e + 1, n, cost, memo)
            );
        }
        memo[seg][start] = best;
        return best;
    }

    public int minimumChanges(String s, int k) {
        int n = s.length();
        char[] ch = s.toCharArray();
        List<Integer>[] factors = new ArrayList[n + 1];
        Arrays.setAll(factors, x -> new ArrayList<>());
        // Precompute the proper divisors of each number
        for (int d = 1; d <= n / 2; d++) {
            for (int m = d * 2; m <= n; m += d) {
                factors[m].add(d);
            }
        }
        int[][] cost = new int[n][n];
        for (int l = 0; l + 1 < n; l++) {
            for (int r = l + 1; r < n; r++) {
                // Each substring must have length at least 2
                cost[l][r] = segmentCost(ch, l, r - l + 1, factors);
            }
        }
        int[][] memo = new int[k + 1][n];
        for (int seg = 0; seg <= k; seg++) {
            Arrays.fill(memo[seg], -1);
        }
        return solve(k, 0, n, cost, memo);
    }
}