#include <vector>
#include <algorithm>

class Solution {
public:
    long long maxTotalValue(std::vector<int>& nums, int k) {
        int max_val = nums[0];
        int min_val = nums[0];
        
        // Find the global maximum and minimum elements
        for (int num : nums) {
            if (num > max_val) max_val = num;
            if (num < min_val) min_val = num;
        }
        
        // Multiply by k, ensuring we cast to long long to prevent overflow
        return static_cast<long long>(k) * (max_val - min_val);
    }
};