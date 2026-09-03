#include <vector>
#include <algorithm>

class Solution {
public:
    // Renamed from isPossibleToConstruct to uniformArray
    bool uniformArray(std::vector<int>& nums1) {
        int min_val = nums1[0];
        bool has_odd = false;
        
        for (int num : nums1) {
            if (num % 2 != 0) {
                has_odd = true;
            }
            if (num < min_val) {
                min_val = num;
            }
        }
        
        // Return true if all numbers are even OR the smallest number is odd
        return !has_odd || (min_val % 2 != 0);
    }
};