class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) {
                // Minimum is on the right side
                left = mid + 1;
            }
            else if (nums[mid] < nums[right]) {
                // Minimum is at mid or on the left side
                right = mid;
            }
            else {
                // Duplicates: cannot determine the side
                right--;
            }
        }

        return nums[left];
    }
};