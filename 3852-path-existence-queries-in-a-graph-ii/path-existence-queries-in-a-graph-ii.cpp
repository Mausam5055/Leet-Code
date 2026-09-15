#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Renamed to match LeetCode's expected function signature
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        // 1. Extract and sort unique values from nums
        vector<int> A = nums;
        sort(A.begin(), A.end());
        A.erase(unique(A.begin(), A.end()), A.end());
        
        int m = A.size();
        
        // 2. Identify Connected Components
        vector<int> comp(m, 0);
        for (int i = 1; i < m; ++i) {
            if (A[i] - A[i - 1] > maxDiff) {
                comp[i] = comp[i - 1] + 1; // Gap too large, new component
            } else {
                comp[i] = comp[i - 1];     // Same component
            }
        }
        
        // 3. Setup Binary Lifting table
        int LOG = 20; // 2^19 > 100,000 limits
        vector<vector<int>> up(m, vector<int>(LOG, 0));
        
        // up[i][0] stores the furthest right index we can reach in 1 jump
        for (int i = 0; i < m; ++i) {
            int nxt = upper_bound(A.begin(), A.end(), A[i] + maxDiff) - A.begin() - 1;
            up[i][0] = nxt;
        }
        
        // Fill the rest of the binary lifting table
        for (int k = 1; k < LOG; ++k) {
            for (int i = 0; i < m; ++i) {
                up[i][k] = up[ up[i][k - 1] ][ k - 1 ];
            }
        }
        
        // 4. Process Queries
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (auto& q : queries) {
            int u = q[0], v = q[1];
            
            // Base Case 1: Same exact node
            if (u == v) {
                ans.push_back(0);
                continue;
            }
            
            int X = nums[u], Y = nums[v];
            
            // Base Case 2: Different nodes but they have the exact same value (difference 0 <= maxDiff)
            if (X == Y) {
                ans.push_back(1);
                continue;
            }
            
            // We always jump from the smaller value to the larger value
            if (X > Y) {
                swap(X, Y);
            }
            
            // Map the values back to their indices in the sorted unique array A
            int idxX = lower_bound(A.begin(), A.end(), X) - A.begin();
            int idxY = lower_bound(A.begin(), A.end(), Y) - A.begin();
            
            // If they are in different components, a path is impossible
            if (comp[idxX] != comp[idxY]) {
                ans.push_back(-1);
                continue;
            }
            
            // Binary Lifting to find the minimum steps
            int curr = idxX;
            int steps = 0;
            
            for (int k = LOG - 1; k >= 0; --k) {
                // If taking 2^k steps doesn't reach or pass our target, we take the leap
                if (up[curr][k] < idxY) {
                    curr = up[curr][k];
                    steps += (1 << k);
                }
            }
            
            // `curr` is now at the furthest point strictly less than `idxY`
            // Taking 1 more step is guaranteed to reach or surpass `idxY`
            ans.push_back(steps + 1);
        }
        
        return ans;
    }
};