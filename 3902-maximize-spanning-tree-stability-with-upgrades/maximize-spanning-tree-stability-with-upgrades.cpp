#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

struct DSU {
    vector<int> parent;
    int components;
    
    DSU(int n) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        components = n;
    }
    
    int find(int i) {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    
    bool unite(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            components--;
            return true;
        }
        return false;
    }
};

class Solution {
public:
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        int max_s = 0;
        int min_must = 2e9 + 7;
        
        DSU base_dsu(n);
        for (const auto& e : edges) {
            if (e[3] == 1) {
                // Mandatory edges form a cycle -> no valid spanning tree exists
                if (!base_dsu.unite(e[0], e[1])) return -1;
                min_must = min(min_must, e[2]);
            }
            max_s = max(max_s, e[2]);
        }
        
        // Initial connectivity check to ensure full connectivity is possible
        DSU all_dsu = base_dsu;
        for (const auto& e : edges) {
            if (e[3] == 0) {
                all_dsu.unite(e[0], e[1]);
            }
        }
        if (all_dsu.components > 1) return -1;
        
        auto check = [&](int X) {
            if (X > min_must) return false;
            
            DSU dsu = base_dsu;
            int upgrades = 0;
            
            // Pass 1: Add non-mandatory edges that meet threshold X without upgrading
            for (const auto& e : edges) {
                if (e[3] == 0 && e[2] >= X) {
                    dsu.unite(e[0], e[1]);
                }
            }
            
            if (dsu.components == 1) return true;
            
            // Pass 2: Add non-mandatory edges that meet threshold X when doubled
            for (const auto& e : edges) {
                if (e[3] == 0 && e[2] < X && 2 * e[2] >= X) {
                    if (dsu.unite(e[0], e[1])) {
                        upgrades++;
                    }
                }
            }
            
            return dsu.components == 1 && upgrades <= k;
        };
        
        int left = 1;
        int right = min((long long)min_must, 2LL * max_s);
        int ans = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                ans = mid;
                left = mid + 1; // Try searching for a higher stability threshold
            } else {
                right = mid - 1;
            }
        }
        
        return ans;
    }
};