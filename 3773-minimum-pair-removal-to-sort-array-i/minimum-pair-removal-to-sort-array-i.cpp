class Solution {
public:
    bool sorted(vector<int>& nums) {
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] < nums[i - 1]) return false;
        }
        return true;
    }

    int minimumPairRemoval(vector<int>& nums) {
        int operations = 0;

        while (!sorted(nums)) {
            int idx = 0;
            int minSum = nums[0] + nums[1];

            for (int i = 1; i < nums.size() - 1; i++) {
                int curSum = nums[i] + nums[i + 1];
                if (curSum < minSum) {
                    minSum = curSum;
                    idx = i;
                }
            }

            nums[idx] = minSum;
            nums.erase(nums.begin() + idx + 1);

            operations++;
        }

        return operations;
    }
};