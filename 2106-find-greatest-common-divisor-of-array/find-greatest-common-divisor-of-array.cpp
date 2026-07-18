#include <vector>
#include <algorithm>
#include <numeric>

class Solution {
public:
    int findGCD(std::vector<int>& nums) {
        // Find both min and max iterators in a single pass
        auto [min_it, max_it] = std::minmax_element(nums.begin(), nums.end());
        
        // Calculate and return the GCD
        return std::gcd(*min_it, *max_it);
    }
};