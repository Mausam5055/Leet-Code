#include <vector>

using namespace std;

class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // Array to store the component ID for each node
        vector<int> component(n, 0);
        int current_id = 0;
        
        // Group nodes into connected components
        for (int i = 1; i < n; ++i) {
            // If the gap exceeds maxDiff, the graph breaks, starting a new component
            if (nums[i] - nums[i - 1] > maxDiff) {
                current_id++;
            }
            component[i] = current_id;
        }
        
        // Process queries in O(1) time each
        vector<bool> answer;
        answer.reserve(queries.size());
        
        for (const auto& q : queries) {
            int u = q[0];
            int v = q[1];
            // If they have the same component ID, a path exists
            answer.push_back(component[u] == component[v]);
        }
        
        return answer;
    }
};