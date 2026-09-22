#include <vector>

using namespace std;

class Solution {
    struct Node {
        int prod;
        int count[5]; 
        
        Node() {
            prod = 1;
            for (int i = 0; i < 5; ++i) {
                count[i] = 0;
            }
        }
    };

    int K;
    vector<Node> tree;

    // Helper to merge two Segment Tree nodes
    Node mergeNodes(const Node& left, const Node& right) {
        Node res;
        res.prod = (left.prod * right.prod) % K;
        
        // Inherit prefixes from the left child
        for (int i = 0; i < K; ++i) {
            res.count[i] = left.count[i];
        }
        
        // Add prefixes that span across the left child and end in the right child
        for (int i = 0; i < K; ++i) {
            if (right.count[i] > 0) {
                int combined_mod = (left.prod * i) % K;
                res.count[combined_mod] += right.count[i];
            }
        }
        return res;
    }

    void build(int node, int L, int R, const vector<int>& nums) {
        if (L == R) {
            tree[node].prod = nums[L] % K;
            for (int i = 0; i < K; ++i) tree[node].count[i] = 0;
            tree[node].count[nums[L] % K] = 1;
            return;
        }
        int mid = L + (R - L) / 2;
        build(2 * node + 1, L, mid, nums);
        build(2 * node + 2, mid + 1, R, nums);
        tree[node] = mergeNodes(tree[2 * node + 1], tree[2 * node + 2]);
    }

    void update(int node, int L, int R, int idx, int val) {
        if (L == R) {
            tree[node].prod = val % K;
            for (int i = 0; i < K; ++i) tree[node].count[i] = 0;
            tree[node].count[val % K] = 1;
            return;
        }
        int mid = L + (R - L) / 2;
        if (idx <= mid) {
            update(2 * node + 1, L, mid, idx, val);
        } else {
            update(2 * node + 2, mid + 1, R, idx, val);
        }
        tree[node] = mergeNodes(tree[2 * node + 1], tree[2 * node + 2]);
    }

    Node query(int node, int L, int R, int qL, int qR) {
        if (qL <= L && R <= qR) {
            return tree[node];
        }
        int mid = L + (R - L) / 2;
        if (qR <= mid) {
            return query(2 * node + 1, L, mid, qL, qR);
        }
        if (qL > mid) {
            return query(2 * node + 2, mid + 1, R, qL, qR);
        }
        return mergeNodes(query(2 * node + 1, L, mid, qL, qR),
                          query(2 * node + 2, mid + 1, R, qL, qR));
    }

public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        K = k;
        int n = nums.size();
        tree.assign(4 * n, Node());
        
        build(0, 0, n - 1, nums);

        vector<int> result;
        result.reserve(queries.size());
        
        for (const auto& q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // 1. Point update that persists
            update(0, 0, n - 1, index, value);
            
            // 2. Compute the result by querying from `start` to `N - 1`
            Node res = query(0, 0, n - 1, start, n - 1);
            result.push_back(res.count[x]);
        }
        
        return result;
    }
};