#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumCost(std::vector<int>& cost) {
        // Sort costs in descending order
        std::sort(cost.rbegin(), cost.rend());
        
        int total_cost = 0;
        for (int i = 0; i < cost.size(); ++i) {
            // Every 3rd item (0-indexed 2, 5, 8) is free
            if (i % 3 != 2) {
                total_cost += cost[i];
            }
        }
        
        return total_cost;
    }
};