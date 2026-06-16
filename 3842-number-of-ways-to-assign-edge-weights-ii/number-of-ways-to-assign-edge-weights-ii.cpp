class Solution {
public:
    static constexpr int MOD = 1e9 + 7;
    static constexpr int LOG = 17;

    vector<vector<int>> up;
    vector<int> depth;
    vector<int> power2;

    void dfs(int u, int p, vector<vector<int>>& adj) {
        up[u][0] = p;

        for (int i = 1; i <= LOG; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }

        for (int v : adj[u]) {
            if (v == p) continue;
            depth[v] = depth[u] + 1;
            dfs(v, u, adj);
        }
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);

        int diff = depth[a] - depth[b];

        for (int i = LOG; i >= 0; i--) {
            if (diff & (1 << i)) {
                a = up[a][i];
            }
        }

        if (a == b) return a;

        for (int i = LOG; i >= 0; i--) {
            if (up[a][i] != up[b][i]) {
                a = up[a][i];
                b = up[b][i];
            }
        }

        return up[a][0];
    }

    vector<int> assignEdgeWeights(vector<vector<int>>& edges,
                                  vector<vector<int>>& queries) {

        int n = edges.size() + 1;

        vector<vector<int>> adj(n + 1);

        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        up.assign(n + 1, vector<int>(LOG + 1));
        depth.assign(n + 1, 0);

        dfs(1, 0, adj);

        power2.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) {
            power2[i] = (2LL * power2[i - 1]) % MOD;
        }

        vector<int> ans;

        for (auto &q : queries) {
            int u = q[0];
            int v = q[1];

            int w = lca(u, v);

            int len = depth[u] + depth[v] - 2 * depth[w];

            if (len == 0) {
                ans.push_back(0);
            } else {
                ans.push_back(power2[len - 1]);
            }
        }

        return ans;
    }
};