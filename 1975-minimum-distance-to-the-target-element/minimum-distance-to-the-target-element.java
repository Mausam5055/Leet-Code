class Solution {
    public int getMinDistance(int[] nums, int target, int start) {
        int minDist = Integer.MAX_VALUE;

        for (int i = 0; i < nums.length; i++) {
            if (nums[i] == target) {
                int dist = Math.abs(i - start);
                minDist = Math.min(minDist, dist);
            }
        }

        return minDist;
    }
}