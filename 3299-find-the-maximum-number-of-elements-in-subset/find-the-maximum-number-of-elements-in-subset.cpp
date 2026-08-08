#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> count;
        for (int num : nums) {
            count[num]++;
        }
        
        int max_len = 0;
        
        // 1. Handle the special case for base 1
        if (count.count(1)) {
            max_len = count[1];
            // The length must be odd
            if (max_len % 2 == 0) {
                max_len--;
            }
        }
        
        // 2. Iterate through all unique numbers
        for (auto const& [key, val] : count) {
            if (key == 1) continue;
            
            long long curr = key;
            int current_len = 0;
            
            // Build the sequence while the current number exists
            while (count.count(curr) && count[curr] > 0) {
                if (count[curr] >= 2) {
                    current_len += 2;
                    curr *= curr;
                } else { 
                    // We found exactly 1, it becomes the perfect peak
                    current_len += 1;
                    break;
                }
            }
            
            // If the loop broke because the number is missing (count == 0),
            // the previous number must act as the peak instead of a pair.
            if (!count.count(curr) || count[curr] == 0) {
                current_len -= 1;
            }
            
            max_len = max(max_len, current_len);
        }
        
        return max_len;
    }
};