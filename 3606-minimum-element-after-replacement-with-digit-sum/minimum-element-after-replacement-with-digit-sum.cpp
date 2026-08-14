#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minElement(vector<int>& nums) {
        int min_val = INT_MAX;
        
        for (int num : nums) {
            int current_sum = 0;
            
            // Calculate the sum of the digits
            while (num > 0) {
                current_sum += num % 10;
                num /= 10;
            }
            
            // Track the minimum digit sum found so far
            min_val = min(min_val, current_sum);
        }
        
        return min_val;
    }
};