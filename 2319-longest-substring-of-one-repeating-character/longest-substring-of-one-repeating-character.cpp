#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Node {
    int max_len;
    int prefix_len;
    int suffix_len;
    char left_char;
    char right_char;
    int len;
};

class Solution {
    vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.len = left.len + right.len;
        res.left_char = left.left_char;
        res.right_char = right.right_char;

        // Calculate new prefix_len
        res.prefix_len = left.prefix_len;
        if (left.prefix_len == left.len && left.right_char == right.left_char) {
            res.prefix_len += right.prefix_len;
        }

        // Calculate new suffix_len
        res.suffix_len = right.suffix_len;
        if (right.suffix_len == right.len && right.left_char == left.right_char) {
            res.suffix_len += left.suffix_len;
        }

        // Calculate new max_len
        res.max_len = max(left.max_len, right.max_len);
        if (left.right_char == right.left_char) {
            res.max_len = max(res.max_len, left.suffix_len + right.prefix_len);
        }

        return res;
    }

    void build(int node, int start, int end, const string& s) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start], 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(2 * node, start, mid, s);
        build(2 * node + 1, mid + 1, end, s);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, char c) {
        if (start == end) {
            tree[node] = {1, 1, 1, c, c, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, c);
        } else {
            update(2 * node + 1, mid + 1, end, idx, c);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.length();
        tree.resize(4 * n);
        
        build(1, 0, n - 1, s);
        
        int k = queryIndices.size();
        vector<int> result(k);
        
        for (int i = 0; i < k; ++i) {
            update(1, 0, n - 1, queryIndices[i], queryCharacters[i]);
            // The global maximum is always stored at the root of the segment tree
            result[i] = tree[1].max_len;
        }
        
        return result;
    }
};