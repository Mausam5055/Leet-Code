import java.util.*;

class Solution {
    public int maxTwoEvents(int[][] events) {
        // Step 1: sort by start time
        Arrays.sort(events, (a, b) -> a[0] - b[0]);

        int n = events.length;

        // Step 2: suffix max array
        int[] maxSuffix = new int[n];
        maxSuffix[n - 1] = events[n - 1][2];

        for (int i = n - 2; i >= 0; i--) {
            maxSuffix[i] = Math.max(maxSuffix[i + 1], events[i][2]);
        }

        int result = 0;

        // Step 3: try each event as first event
        for (int i = 0; i < n; i++) {
            int end = events[i][1];
            int value = events[i][2];

            // binary search for next event
            int left = i + 1, right = n - 1;
            int nextIndex = n;

            while (left <= right) {
                int mid = (left + right) / 2;
                if (events[mid][0] > end) {
                    nextIndex = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            int total = value;
            if (nextIndex < n) {
                total += maxSuffix[nextIndex];
            }

            result = Math.max(result, total);
        }

        return result;
    }
}