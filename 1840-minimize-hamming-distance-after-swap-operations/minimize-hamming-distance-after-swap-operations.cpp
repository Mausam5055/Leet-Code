class Solution {
    vector<int> parent, rank;

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);

        return parent[x];
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);

        if (a == b)
            return;

        if (rank[a] < rank[b])
            swap(a, b);

        parent[b] = a;

        if (rank[a] == rank[b])
            rank[a]++;
    }

public:
    int minimumHammingDistance(vector<int>& source,
                               vector<int>& target,
                               vector<vector<int>>& allowedSwaps) {

        int n = source.size();

        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++)
            parent[i] = i;

        // Connect all swappable indices
        for (auto &swap : allowedSwaps) {
            unite(swap[0], swap[1]);
        }

        // Store frequencies of source values
        // inside each connected component
        unordered_map<int, unordered_map<int, int>> freq;

        for (int i = 0; i < n; i++) {
            int root = find(i);
            freq[root][source[i]]++;
        }

        int ans = 0;

        // Try matching target values
        for (int i = 0; i < n; i++) {

            int root = find(i);

            if (freq[root][target[i]] > 0) {
                freq[root][target[i]]--;
            }
            else {
                ans++;
            }
        }

        return ans;
    }
};