class Solution {
public:
    bool check(vector<int>& nums) {
        int drops = 0;
        int n = nums.size();
        
        for (int i = 0; i < n; i++) {
            // Compare current element with the next element (wrapping around to the start)
            if (nums[i] > nums[(i + 1) % n]) {
                drops++;
            }
            
            // If we find more than 1 drop, it's invalid
            if (drops > 1) {
                return false;
            }
        }
        
        return true;
    }
};