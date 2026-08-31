#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // If mid element is greater than the rightmost element, 
            // the smallest value must be to the right.
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } 
            // Otherwise, the smallest value is at mid or to the left.
            else {
                right = mid;
            }
        }
        
        // left and right converge to the index of the minimum element
        return nums[left];
    }
};