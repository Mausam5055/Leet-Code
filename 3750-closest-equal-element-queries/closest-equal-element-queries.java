import java.util.*;

class Solution {
    public List<Integer> solveQueries(int[] nums, int[] queries) {
        int n = nums.length;
        
        // Step 1: Map value → indices
        Map<Integer, List<Integer>> map = new HashMap<>();
        
        for (int i = 0; i < n; i++) {
            map.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }
        
        List<Integer> result = new ArrayList<>();
        
        // Step 2: Process queries
        for (int q : queries) {
            int val = nums[q];
            List<Integer> list = map.get(val);
            
            if (list.size() == 1) {
                result.add(-1);
                continue;
            }
            
            // Binary search to find position
            int idx = Collections.binarySearch(list, q);
            
            int size = list.size();
            
            // Neighbor indices (circular)
            int left = list.get((idx - 1 + size) % size);
            int right = list.get((idx + 1) % size);
            
            // Compute circular distance
            int dist1 = Math.abs(q - left);
            dist1 = Math.min(dist1, n - dist1);
            
            int dist2 = Math.abs(q - right);
            dist2 = Math.min(dist2, n - dist2);
            
            result.add(Math.min(dist1, dist2));
        }
        
        return result;
    }
}