import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

class Solution {
    public long minimumTotalDistance(List<Integer> robot, int[][] factory) {
        // 1. Sort robots and factories by their positions on the X-axis
        Collections.sort(robot);
        Arrays.sort(factory, (a, b) -> Integer.compare(a[0], b[0]));

        // 2. Flatten the factories array
        // A factory at pos 'x' with limit 'k' becomes 'k' individual slots at pos 'x'
        List<Integer> flatFactory = new ArrayList<>();
        for (int[] f : factory) {
            int pos = f[0];
            int limit = f[1];
            for (int i = 0; i < limit; i++) {
                flatFactory.add(pos);
            }
        }

        // Initialize memoization table with -1
        int n = robot.size();
        int m = flatFactory.size();
        long[][] memo = new long[n][m];
        for (long[] row : memo) {
            Arrays.fill(row, -1L);
        }

        return solve(0, 0, robot, flatFactory, memo);
    }

    private long solve(int rIdx, int fIdx, List<Integer> robot, List<Integer> flatFactory, long[][] memo) {
        // Base Case 1: All robots have been assigned to a factory
        if (rIdx == robot.size()) {
            return 0;
        }
        
        // Base Case 2: We ran out of factory slots, but robots are still left
        if (fIdx == flatFactory.size()) {
            return (long) 1e15; // Return a massive number representing an invalid path
        }

        // Return cached result if already computed
        if (memo[rIdx][fIdx] != -1L) {
            return memo[rIdx][fIdx];
        }

        // Choice 1: Skip the current factory slot
        long skip = solve(rIdx, fIdx + 1, robot, flatFactory, memo);

        // Choice 2: Assign the current robot to the current factory slot
        long distance = Math.abs((long) robot.get(rIdx) - flatFactory.get(fIdx));
        long take = distance + solve(rIdx + 1, fIdx + 1, robot, flatFactory, memo);

        // Store the minimum of both choices
        return memo[rIdx][fIdx] = Math.min(skip, take);
    }
}