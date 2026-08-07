#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        // Map to store the last two seen indices for each number: {second_last, last}
        unordered_map<int, pair<int, int>> pos;
        int min_dist = 1e9;
        
        for (int i = 0; i < nums.size(); i++) {
            int val = nums[i];
            
            if (pos.find(val) == pos.end()) {
                // First time seeing this number
                pos[val] = {-1, i}; 
            } else {
                int sec_last = pos[val].first;
                int last = pos[val].second;
                
                // If we have seen it at least twice before, calculate the distance
                if (sec_last != -1) {
                    min_dist = min(min_dist, i - sec_last);
                }
                
                // Shift the history: the old "last" becomes "second_last", current becomes "last"
                pos[val] = {last, i};
            }
        }
        
        // If we never found 3 equal elements, return -1. Otherwise, return 2 * (k - i)
        return min_dist == 1e9 ? -1 : min_dist * 2;
    }
};