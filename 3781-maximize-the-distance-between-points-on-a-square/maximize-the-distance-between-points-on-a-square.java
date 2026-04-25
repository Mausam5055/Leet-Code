import java.util.Arrays;

class Solution {
    // Unroll the 2D perimeter into a 1D line segment [0, 4*side)
    private long mapTo1D(int x, int y, int s) {
        if (y == 0) return (long) x;                             // Bottom edge
        if (x == s) return (long) s + y;                         // Right edge
        if (y == s) return 2L * s + (s - x);                     // Top edge
        if (x == 0) return 3L * s + (s - y);                     // Left edge
        return 0;
    }

    private boolean check(long mid, int N, int k, long[] A2, long totalLen) {
        int n2 = 2 * N;
        int[] nxt = new int[n2 + 1];
        nxt[n2] = n2; 
        
        // Two-pointer precomputation of the next valid point
        int j = 0;
        for (int i = 0; i < n2; ++i) {
            while (j < n2 && A2[j] - A2[i] < mid) {
                j++;
            }
            nxt[i] = j;
        }

        // Try placing K points starting from every possible initial point
        for (int i = 0; i < N; ++i) {
            int curr = i;
            int steps = 1;
            while (steps < k && curr < n2) {
                curr = nxt[curr];
                steps++;
            }
            // Check if the k-th point successfully wrapped around without overlapping
            if (curr < n2 && A2[curr] <= A2[i] + totalLen - mid) {
                return true;
            }
        }
        return false;
    }

    public int maxDistance(int side, int[][] points, int k) {
        int N = points.length;
        long[] A = new long[N];
        
        for (int i = 0; i < N; ++i) {
            A[i] = mapTo1D(points[i][0], points[i][1], side);
        }
        Arrays.sort(A);

        // Duplicate the array to handle circular nature
        long[] A2 = new long[2 * N];
        long totalLen = 4L * side;
        for (int i = 0; i < N; ++i) {
            A2[i] = A[i];
            A2[i + N] = A[i] + totalLen;
        }

        // Binary search for the maximum possible minimum distance
        long low = 1, high = side;
        long ans = 0;

        while (low <= high) {
            long mid = low + (high - low) / 2;
            if (check(mid, N, k, A2, totalLen)) {
                ans = mid;
                low = mid + 1; // Try for a larger minimum distance
            } else {
                high = mid - 1; // Distance too large, scale back
            }
        }

        return (int) ans;
    }
}