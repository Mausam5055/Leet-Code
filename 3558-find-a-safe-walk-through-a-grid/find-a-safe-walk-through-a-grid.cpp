class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();

        const int INF = 1e9;

        vector<vector<int>> dist(m, vector<int>(n, INF));

        deque<pair<int, int>> dq;

        // Starting cell also affects health
        dist[0][0] = grid[0][0];
        dq.push_front({0, 0});

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!dq.empty()) {
            auto [r, c] = dq.front();
            dq.pop_front();

            for (int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                // Check bounds
                if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                    continue;

                int cost = grid[nr][nc];

                // New health loss
                if (dist[r][c] + cost < dist[nr][nc]) {
                    dist[nr][nc] = dist[r][c] + cost;

                    if (cost == 0)
                        dq.push_front({nr, nc});
                    else
                        dq.push_back({nr, nc});
                }
            }
        }

        // We must still have at least 1 health
        return health - dist[m - 1][n - 1] >= 1;
    }
};