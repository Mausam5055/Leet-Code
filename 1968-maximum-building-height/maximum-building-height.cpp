#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        // Add the implicit restriction for building 1
        restrictions.push_back({1, 0});
        
        // Sort restrictions based on building ID
        sort(restrictions.begin(), restrictions.end());
        
        // Add dummy restriction for the last building if it doesn't exist
        if (restrictions.back()[0] != n) {
            restrictions.push_back({n, n - 1});
        }
        
        int m = restrictions.size();
        
        // Left-to-Right Pass
        for (int i = 1; i < m; ++i) {
            long long prev_id = restrictions[i-1][0], prev_h = restrictions[i-1][1];
            long long curr_id = restrictions[i][0], curr_h = restrictions[i][1];
            restrictions[i][1] = min((long long)curr_h, prev_h + (curr_id - prev_id));
        }
        
        // Right-to-Left Pass
        for (int i = m - 2; i >= 0; --i) {
            long long next_id = restrictions[i+1][0], next_h = restrictions[i+1][1];
            long long curr_id = restrictions[i][0], curr_h = restrictions[i][1];
            restrictions[i][1] = min((long long)curr_h, next_h + (next_id - curr_id));
        }
        
        int max_height = 0;
        
        // Find the peak between every pair of adjacent restrictions
        for (int i = 1; i < m; ++i) {
            long long id1 = restrictions[i-1][0], h1 = restrictions[i-1][1];
            long long id2 = restrictions[i][0], h2 = restrictions[i][1];
            
            int peak = (h1 + h2 + (id2 - id1)) / 2;
            max_height = max(max_height, peak);
        }
        
        return max_height;
    }
};