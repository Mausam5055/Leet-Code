class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();
        
        // If the array has 1 or 2 elements, we must delete all of them
        if (n <= 2) {
            return n;
        }
        
        // Find the indices of the minimum and maximum elements
        int min_idx = 0;
        int max_idx = 0;
        
        for (int k = 1; k < n; ++k) {
            if (nums[k] < nums[min_idx]) min_idx = k;
            if (nums[k] > nums[max_idx]) max_idx = k;
        }
        
        // Identify which index comes first (i) and which comes second (j)
        int i = min(min_idx, max_idx);
        int j = max(min_idx, max_idx);
        
        // Calculate the 3 removal strategies
        int both_from_front = j + 1;
        int both_from_back = n - i;
        int front_and_back = (i + 1) + (n - j);
        
        // Return the minimum deletions required
        return min({both_from_front, both_from_back, front_and_back});
    }
};