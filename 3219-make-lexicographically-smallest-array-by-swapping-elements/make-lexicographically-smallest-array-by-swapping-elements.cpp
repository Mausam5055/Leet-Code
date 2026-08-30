#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        
        // Pair up each number with its original index
        vector<pair<int, int>> sorted_nums(n);
        for (int i = 0; i < n; ++i) {
            sorted_nums[i] = {nums[i], i};
        }
        
        // Sort the pairs based on the values
        sort(sorted_nums.begin(), sorted_nums.end());
        
        vector<int> result(n);
        int i = 0;
        
        // Group elements into connected components
        while (i < n) {
            int j = i + 1;
            // Extend the component as long as the difference between adjacent sorted elements is <= limit
            while (j < n && sorted_nums[j].first - sorted_nums[j - 1].first <= limit) {
                j++;
            }
            
            // Extract all original indices for the current component
            vector<int> indices;
            for (int k = i; k < j; ++k) {
                indices.push_back(sorted_nums[k].second);
            }
            
            // Sort the indices so we can place the smallest values into the earliest available slots
            sort(indices.begin(), indices.end());
            
            // Re-assign the sorted values to the sorted indices in the result array
            for (int k = 0; k < indices.size(); ++k) {
                result[indices[k]] = sorted_nums[i + k].first;
            }
            
            // Move to the start of the next component
            i = j;
        }
        
        return result;
    }
};