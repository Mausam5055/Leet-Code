class Solution {
public:
    bool isGood(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int n = nums.back();

        // Size must be n + 1
        if (nums.size() != n + 1)
            return false;

        // Check 1 to n-1
        for (int i = 0; i < n - 1; i++) {
            if (nums[i] != i + 1)
                return false;
        }

        // Last two elements must be n
        return nums[n - 1] == n && nums[n] == n;
    }
};