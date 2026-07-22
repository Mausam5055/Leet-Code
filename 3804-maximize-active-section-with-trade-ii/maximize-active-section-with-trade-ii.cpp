#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int total_ones = 0;
        for (char c : s) {
            if (c == '1') total_ones++;
        }

        vector<pair<int, int>> blocks;
        vector<int> starts, ends;
        
        // Step 1: Extract all contiguous blocks of '0's
        for (int i = 0; i < n; ) {
            if (s[i] == '0') {
                int j = i;
                while (j < n && s[j] == '0') j++;
                blocks.push_back({i, j - 1});
                starts.push_back(i);
                ends.push_back(j - 1);
                i = j;
            } else {
                i++;
            }
        }

        int m = blocks.size();
        
        // Step 2: Build a Sparse Table (RMQ) for the sum of adjacent '0' blocks
        vector<vector<int>> st;
        if (m >= 2) {
            int max_log = log2(m) + 1;
            st.assign(m - 1, vector<int>(max_log, 0));
            
            for (int i = 0; i < m - 1; i++) {
                int len1 = blocks[i].second - blocks[i].first + 1;
                int len2 = blocks[i + 1].second - blocks[i + 1].first + 1;
                st[i][0] = len1 + len2;
            }
            
            for (int j = 1; j < max_log; j++) {
                for (int i = 0; i + (1 << j) <= m - 1; i++) {
                    st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
                }
            }
        }

        // Helper Lambda for O(1) RMQ
        auto query_st = [&](int l, int r) {
            if (l > r) return 0;
            int len = r - l + 1;
            int k = log2(len);
            return max(st[l][k], st[r - (1 << k) + 1][k]);
        };

        vector<int> answer;
        answer.reserve(queries.size());

        // Step 3: Process each query
        for (const auto& q : queries) {
            int L = q[0];
            int R = q[1];

            int a = lower_bound(ends.begin(), ends.end(), L) - ends.begin();
            int b = upper_bound(starts.begin(), starts.end(), R) - starts.begin() - 1;

            if (a > b || a == m || b < 0) {
                // No '0' blocks in range
                answer.push_back(total_ones);
            } else if (a == b) {
                // Only one '0' block in range, can't perform a trade
                answer.push_back(total_ones);
            } else if (b == a + 1) {
                // Exactly two '0' blocks in range
                int z_a = blocks[a].second - max(L, blocks[a].first) + 1;
                int z_b = min(R, blocks[b].second) - blocks[b].first + 1;
                answer.push_back(total_ones + z_a + z_b);
            } else {
                // More than two '0' blocks in range
                int z_a = blocks[a].second - max(L, blocks[a].first) + 1;
                int z_b = min(R, blocks[b].second) - blocks[b].first + 1;
                
                int len_a_next = blocks[a + 1].second - blocks[a + 1].first + 1;
                int len_b_prev = blocks[b - 1].second - blocks[b - 1].first + 1;
                
                int gain_left = z_a + len_a_next;
                int gain_right = len_b_prev + z_b;
                
                int max_gain = max(gain_left, gain_right);
                
                // Maximize with completely enclosed adjacent blocks via Sparse Table
                if (b - 1 >= a + 2) {
                    max_gain = max(max_gain, query_st(a + 1, b - 2));
                }
                
                answer.push_back(total_ones + max_gain);
            }
        }

        return answer;
    }
};