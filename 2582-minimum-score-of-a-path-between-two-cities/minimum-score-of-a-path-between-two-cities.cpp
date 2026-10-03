class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        // Build the adjacency list
        vector<vector<pair<int, int>>> adj(n + 1);
        for (const auto& road : roads) {
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }
        
        vector<bool> visited(n + 1, false);
        queue<int> q;
        q.push(1);
        visited[1] = true;
        
        int min_score = 1e9; // Initialize with a large number
        
        // Traverse the connected component
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            for (auto& edge : adj[node]) {
                int neighbor = edge.first;
                int distance = edge.second;
                
                // Always update the minimum score for any edge connected to our component
                min_score = min(min_score, distance);
                
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        return min_score;
    }
};