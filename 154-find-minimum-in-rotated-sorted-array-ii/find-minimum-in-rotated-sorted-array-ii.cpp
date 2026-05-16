class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) {
                // minimum is in right half
                left = mid + 1;
            }
            else if (nums[mid] < nums[right]) {
                // minimum is at mid or left half
                right = mid;
            }
            else {
                // duplicates, can't decide
                right--;
            }
        }

        return nums[left];
    }
};