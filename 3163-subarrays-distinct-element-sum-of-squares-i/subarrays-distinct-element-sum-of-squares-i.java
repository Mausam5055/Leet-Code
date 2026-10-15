class Solution {
    public int sumCounts(List<Integer> nums) {
        int ans = 0, n = nums.size();

        // Step 1: every index i is a start of a subarray
        for (int i = 0; i < n; i++) {
            // a NEW empty set for every start
            Set<Integer> set = new HashSet<>();

            // Step 2: grow the end j to the right
            for (int j = i; j < n; j++) {
                set.add(nums.get(j));        // duplicates are ignored
                int count = set.size();      // distinct count of nums[i..j]
                ans += count * count;        // add its square
            }
        }
        return ans;
    }
}