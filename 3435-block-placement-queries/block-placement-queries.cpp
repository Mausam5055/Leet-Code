#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class SegmentTree {
    int n;
    vector<int> tree;

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = start + (end - start) / 2;
        return max(query(2 * node, start, mid, l, r),
                   query(2 * node + 1, mid + 1, end, l, r));
    }

public:
    // Initialize tree with given maximum coordinate
    SegmentTree(int n) {
        this->n = n;
        tree.assign(4 * n + 1, 0);
    }

    void update(int idx, int val) {
        update(1, 0, n, idx, val);
    }

    int query(int l, int r) {
        if (l > r) return 0;
        return query(1, 0, n, l, r);
    }
};

class Solution {
public:
    vector<bool> getResults(vector<vector<int>>& queries) {
        // 1. Find the maximum possible x to set bounds for the Segment Tree
        int max_x = 0;
        for (const auto& q : queries) {
            max_x = max(max_x, q[1]);
        }

        SegmentTree segTree(max_x + 1);
        set<int> obstacles;
        obstacles.insert(0); // The origin acts as an immutable boundary

        vector<bool> results;

        for (const auto& q : queries) {
            if (q[0] == 1) { // Type 1: Place an obstacle
                int x = q[1];
                
                // Find right and left neighbors
                auto it = obstacles.upper_bound(x);
                int prv = *prev(it);

                // Create the new gap ending at x
                segTree.update(x, x - prv);

                // If a neighbor exists to the right, shrink its gap
                if (it != obstacles.end()) {
                    int nxt = *it;
                    segTree.update(nxt, nxt - x);
                }

                obstacles.insert(x);
                
            } else { // Type 2: Check for block placement
                int x = q[1], sz = q[2];
                auto it = obstacles.upper_bound(x);
                int prv = *prev(it);

                // Check the gap directly touching 'x' first
                if (x - prv >= sz) {
                    results.push_back(true);
                } else {
                    // Otherwise, check the max historical gap strictly before 'x'
                    int max_gap = segTree.query(0, prv);
                    results.push_back(max_gap >= sz);
                }
            }
        }

        return results;
    }
};