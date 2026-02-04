class Solution {
    public long maxSumTrionic(int[] nums) {
        int n = nums.length;
        if (n < 4) return 0; // Constraint says n >= 4, but good safety check

        // 1. Precompute Max Increasing Suffix Sums (incEnd)
        // incEnd[i] stores the max sum of a strictly increasing subarray ending at i
        long[] incEnd = new long[n];
        incEnd[0] = nums[0];
        for (int i = 1; i < n; ++i) {
            if (nums[i] > nums[i - 1]) {
                incEnd[i] = Math.max((long) nums[i], nums[i] + incEnd[i - 1]);
            } else {
                incEnd[i] = nums[i];
            }
        }

        // 2. Precompute Max Increasing Prefix Sums (incStart)
        // incStart[i] stores the max sum of a strictly increasing subarray starting at i
        long[] incStart = new long[n];
        incStart[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            if (nums[i] < nums[i + 1]) {
                incStart[i] = Math.max((long) nums[i], nums[i] + incStart[i + 1]);
            } else {
                incStart[i] = nums[i];
            }
        }

        // 3. Prefix Sums for O(1) range sum calculation of the middle decreasing part
        long[] P = new long[n + 1];
        for (int i = 0; i < n; ++i) {
            P[i + 1] = P[i] + nums[i];
        }

        long globalMax = Long.MIN_VALUE;

        // 4. Iterate through the array to find Strictly Decreasing Segments
        int i = 0;
        while (i < n - 1) {
            if (nums[i] > nums[i + 1]) {
                // Found the start of a decreasing segment at i
                int j = i;
                // Find the end of this decreasing segment
                while (j < n - 1 && nums[j] > nums[j + 1]) {
                    j++;
                }
                
                // Segment is nums[i...j]. We need pivots p, q such that i <= p < q <= j.
                // We maximize: (incEnd[p-1] - P[p]) + (incStart[q+1] + P[q+1])
                
                long currentMaxL = Long.MIN_VALUE / 2; // Avoid overflow
                
                // Iterate through the decreasing segment
                for (int k = i + 1; k <= j; ++k) {
                    // Potential 'p' is k-1
                    int pCand = k - 1;
                    // Check if pCand is a valid peak for the left leg
                    if (pCand > 0 && nums[pCand] > nums[pCand - 1]) {
                        long valL = incEnd[pCand - 1] - P[pCand];
                        if (valL > currentMaxL) {
                            currentMaxL = valL;
                        }
                    }

                    // Potential 'q' is k
                    int qCand = k;
                    // Check if qCand is a valid valley for the right leg
                    if (qCand < n - 1 && nums[qCand] < nums[qCand + 1]) {
                        if (currentMaxL > Long.MIN_VALUE / 2) {
                            long valR = incStart[qCand + 1] + P[qCand + 1];
                            long total = currentMaxL + valR;
                            if (total > globalMax) {
                                globalMax = total;
                            }
                        }
                    }
                }
                
                // Move iterator to end of this segment
                i = j;
            } else {
                i++;
            }
        }

        return globalMax;
    }
}