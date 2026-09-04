class Solution {
    public long[] distance(int[] nums) {
        int n = nums.length;
        Map<Integer, List<Integer>> indicesMap = new HashMap<>();
        
        for (int i = 0; i < n; i++) {
            indicesMap.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }
        
        long[] ans = new long[n];
        
        for (List<Integer> indices : indicesMap.values()) {
            int k = indices.size();
            if (k == 1) continue;
            
            long prefixSum = 0;
            long suffixSum = 0;
            
            for (int idx : indices) {
                suffixSum += idx;
            }
            
            for (int m = 0; m < k; m++) {
                long i = indices.get(m);
                suffixSum -= i;
                
                long leftDiff = m * i - prefixSum;
                long rightDiff = suffixSum - (k - 1 - m) * i;
                
                ans[(int)i] = leftDiff + rightDiff;
                prefixSum += i;
            }
        }
        
        return ans;
    }
}