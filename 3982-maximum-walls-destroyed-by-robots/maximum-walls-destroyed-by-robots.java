import java.util.*;

class Solution {
    
    // Equivalent to Python's bisect.bisect_left
    private int bisectLeft(int[] arr, int val) {
        int l = 0, r = arr.length;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] >= val) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }

    // Equivalent to Python's bisect.bisect_right
    private int bisectRight(int[] arr, int val) {
        int l = 0, r = arr.length;
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (arr[mid] > val) {
                r = mid;
            } else {
                l = mid + 1;
            }
        }
        return l;
    }

    // Renamed from maximumWalls to maxWalls to match LeetCode's expected signature
    public int maxWalls(int[] robots, int[] distance, int[] walls) {
        int n = robots.length;
        
        // Pair robots with their distances and sort them by position
        int[][] robotData = new int[n][2];
        Set<Integer> robotPositions = new HashSet<>();
        
        for (int i = 0; i < n; i++) {
            robotData[i][0] = robots[i];
            robotData[i][1] = distance[i];
            robotPositions.add(robots[i]);
        }
        
        Arrays.sort(robotData, (a, b) -> Integer.compare(a[0], b[0]));

        // 1. Pre-process and remove walls exactly at robot positions
        int wallsAtRobots = 0;
        List<Integer> filteredWallsList = new ArrayList<>();
        
        for (int w : walls) {
            if (robotPositions.contains(w)) {
                wallsAtRobots++;
            } else {
                filteredWallsList.add(w);
            }
        }
        
        // Sort the remaining walls strictly existing in the gaps
        int[] W = new int[filteredWallsList.size()];
        for (int i = 0; i < W.length; i++) {
            W[i] = filteredWallsList.get(i);
        }
        Arrays.sort(W);

        if (n == 0) return wallsAtRobots;

        // DP table: dp[i][0] -> Robot i shoots LEFT, dp[i][1] -> Robot i shoots RIGHT
        int[][] dp = new int[n][2];
        
        // --- BASE CASE: Robot 0 ---
        int R0 = robotData[0][0];
        int D0 = robotData[0][1];
        
        int idxStart = 0; 
        int idxEnd = bisectLeft(W, R0);
        
        // Walls covered by Robot 0 shooting LEFT (into Segment 0)
        int reachLeft = bisectLeft(W, R0 - D0);
        int actualReach = Math.max(reachLeft, idxStart);
        int cL_0 = Math.max(0, idxEnd - actualReach);
        
        dp[0][0] = cL_0;
        dp[0][1] = 0;
        
        // --- DP TRANSITIONS ---
        for (int i = 1; i < n; i++) {
            int R_prev = robotData[i-1][0];
            int D_prev = robotData[i-1][1];
            int R_curr = robotData[i][0];
            int D_curr = robotData[i][1];
            
            // Identify walls in the gap between Robot i-1 and Robot i
            idxStart = bisectRight(W, R_prev);
            idxEnd = bisectLeft(W, R_curr);
            int T = Math.max(0, idxEnd - idxStart); // Total walls in this gap
            
            // Walls covered if previous robot shoots RIGHT
            int reachRight = bisectRight(W, R_prev + D_prev);
            int actualReachRight = Math.min(reachRight, idxEnd);
            int cR_prev = Math.max(0, actualReachRight - idxStart);
            
            // Walls covered if current robot shoots LEFT
            int reachLeftCurr = bisectLeft(W, R_curr - D_curr);
            int actualReachLeft = Math.max(reachLeftCurr, idxStart);
            int cL_curr = Math.max(0, idxEnd - actualReachLeft);
            
            // Transition 1: Current robot shoots LEFT
            dp[i][0] = Math.max(
                dp[i-1][0] + cL_curr,                               // Prev shot left (no overlap)
                dp[i-1][1] + Math.min(T, cR_prev + cL_curr)         // Prev shot right (potential overlap)
            );
            
            // Transition 2: Current robot shoots RIGHT
            dp[i][1] = Math.max(
                dp[i-1][0],                                         // Prev shot left (no coverage in gap)
                dp[i-1][1] + cR_prev                                // Prev shot right
            );
        }
        
        // --- FINAL SEGMENT (Right of the last robot) ---
        int R_last = robotData[n-1][0];
        int D_last = robotData[n-1][1];
        
        idxStart = bisectRight(W, R_last);
        idxEnd = W.length;
        
        int reachRightLast = bisectRight(W, R_last + D_last);
        int actualReachRightLast = Math.min(reachRightLast, idxEnd);
        int cR_last = Math.max(0, actualReachRightLast - idxStart);
        
        // Max of (Last robot shot left, Last robot shot right + its coverage to the right)
        int maxWallsInGaps = Math.max(dp[n-1][0], dp[n-1][1] + cR_last);
        
        // Total = walls maximized in gaps + walls trivially destroyed by standing on them
        return maxWallsInGaps + wallsAtRobots;
    }
}