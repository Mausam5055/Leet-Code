class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();

        // Place each number in its correct position if possible
        for (int i = 0; i < n; i++) {
            while (
                nums[i] >= 1 &&
                nums[i] <= n &&
                nums[nums[i] - 1] != nums[i]
            ) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }

        // Find the first index where value is incorrect
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1)
                return i + 1;
        }

        // All numbers from 1 to n are present
        return n + 1;
    }
};
