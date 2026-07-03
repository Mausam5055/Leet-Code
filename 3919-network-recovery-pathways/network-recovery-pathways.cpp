#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        
        // 1. Build adjacency list for online nodes only
        vector<vector<pair<int, int>>> adj(n);
        vector<int> inDegree(n, 0);
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            
            // Skip edges involving offline nodes
            if (!online[u] || !online[v]) continue;
            
            adj[u].push_back({v, cost});
            inDegree[v]++;
        }
        
        // 2. Compute Topological Sort using Kahn's Algorithm
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (online[i] && inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                if (--inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        // Lambda helper to check if a valid path exists with minimum edge cost >= X
        auto isValid = [&](int X) -> bool {
            // Use long long to prevent overflow during accumulation
            vector<long long> dist(n, 5e13 + 7); 
            dist[0] = 0;
            
            for (int u : topoOrder) {
                if (dist[u] > k) continue; // Optimization: can't reach or already exceeds k
                
                for (const auto& neighbor : adj[u]) {
                    int v = neighbor.first;
                    int cost = neighbor.second;
                    
                    if (cost >= X) {
                        if (dist[u] + cost < dist[v]) {
                            dist[v] = dist[u] + cost;
                        }
                    }
                }
            }
            return dist[n - 1] <= k;
        };
        
        // 3. Binary Search for the maximum score
        int low = 0, high = 1e9, ans = -1;
        
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (isValid(mid)) {
                ans = mid;       // mid is possible, try to find a larger minimum edge cost
                low = mid + 1;
            } else {
                high = mid - 1;  // mid is too restrictive, lower the threshold
            }
        }
        
        return ans;
    }
};