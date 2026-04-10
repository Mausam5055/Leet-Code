import java.util.*;

class Solution {
    public int minimumDistance(int[] nums) {
        // Step 1: store indices of each number
        Map<Integer, List<Integer>> map = new HashMap<>();

        for (int i = 0; i < nums.length; i++) {
            map.putIfAbsent(nums[i], new ArrayList<>());
            map.get(nums[i]).add(i);
        }

        int minDist = Integer.MAX_VALUE;

        // Step 2: check each number
        for (List<Integer> list : map.values()) {
            if (list.size() >= 3) {
                // Step 3: check consecutive triples
                for (int i = 0; i <= list.size() - 3; i++) {
                    int first = list.get(i);
                    int third = list.get(i + 2);

                    int dist = 2 * (third - first);
                    minDist = Math.min(minDist, dist);
                }
            }
        }

        return minDist == Integer.MAX_VALUE ? -1 : minDist;
    }
}