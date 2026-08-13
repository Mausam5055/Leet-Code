#include <vector>

using namespace std;

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int n = nums.size();
        // Initialize answer array with the pivot value
        vector<int> ans(n, pivot);
        
        int left = 0;
        int right = n - 1;
        
        // Single pass reading from both ends
        for (int i = 0, j = n - 1; i < n; ++i, --j) {
            // Place smaller elements from the left
            if (nums[i] < pivot) {
                ans[left++] = nums[i];
            }
            // Place larger elements from the right
            if (nums[j] > pivot) {
                ans[right--] = nums[j];
            }
        }
        
        return ans;
    }
};