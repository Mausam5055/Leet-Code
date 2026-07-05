#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        
        // Group indices by their corresponding values in nums
        unordered_map<int, vector<int>> val_to_indices;
        for (int i = 0; i < n; ++i) {
            val_to_indices[nums[i]].push_back(i);
        }
        
        // Array to store the precomputed minimum distance for every index
        // Initialized to -1 (the default for values with no equal elements)
        vector<int> min_dist(n, -1);
        
        for (const auto& pair : val_to_indices) {
            const vector<int>& indices = pair.second;
            int k = indices.size();
            
            // Only process if the element appears more than once
            if (k > 1) {
                for (int i = 0; i < k; ++i) {
                    int curr_idx = indices[i];
                    
                    // Get left and right neighbors in the grouped list (with wrap-around)
                    int left_idx = indices[(i - 1 + k) % k];
                    int right_idx = indices[(i + 1) % k];
                    
                    // Calculate circular distances
                    // Note: C++ modulo can be negative, so we add 'n' before taking % n
                    int dist_left = (curr_idx - left_idx + n) % n;
                    int dist_right = (right_idx - curr_idx + n) % n;
                    
                    min_dist[curr_idx] = min(dist_left, dist_right);
                }
            }
        }
        
        // Map the precomputed distances to the queried indices
        vector<int> ans;
        ans.reserve(queries.size()); // Pre-allocate memory for speed
        for (int q : queries) {
            ans.push_back(min_dist[q]);
        }
        
        return ans;
    }
};