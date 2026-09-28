#include <vector>
#include <algorithm>

using namespace std;

// Structure to store interval details
struct Node {
    int l, r, w, id;
};

// State to store the dynamic programming results optimally
struct State {
    long long score;
    int count;
    int ids[4];

    State() {
        score = 0;
        count = 0;
    }
};

// Compare two states: maximize score, then minimize lexicographical sequence
bool isBetter(const State& a, const State& b) {
    if (a.score != b.score) {
        return a.score > b.score;
    }
    // If scores are tied, prefer lexicographically smaller index sequences
    for (int i = 0; i < min(a.count, b.count); ++i) {
        if (a.ids[i] != b.ids[i]) {
            return a.ids[i] < b.ids[i];
        }
    }
    return a.count < b.count;
}

// Function to transition state when an interval is chosen
State takeState(long long w, int id, const State& next_state) {
    State res;
    res.score = w + next_state.score;
    res.count = next_state.count + 1;
    
    int j = 0;
    bool inserted = false;
    // Merge the current `id` with `next_state.ids` in sorted order
    for (int k = 0; k < res.count; ++k) {
        if (!inserted && (j == next_state.count || id < next_state.ids[j])) {
            res.ids[k] = id;
            inserted = true;
        } else {
            res.ids[k] = next_state.ids[j++];
        }
    }
    return res;
}

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<Node> arr(n);
        
        for (int i = 0; i < n; ++i) {
            arr[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }

        // Sort intervals by start time. If tied, sort by end time.
        sort(arr.begin(), arr.end(), [](const Node& a, const Node& b) {
            if (a.l != b.l) return a.l < b.l;
            return a.r < b.r; 
        });

        vector<vector<State>> dp(n + 1, vector<State>(5));

        // Evaluate starting from the last interval down to the first
        for (int i = n - 1; i >= 0; --i) {
            int target = arr[i].r;
            
            // Binary search to find the first interval that starts strictly after arr[i] ends
            int low = i + 1, high = n, nxt = n;
            while (low < high) {
                int mid = low + (high - low) / 2;
                if (arr[mid].l > target) {
                    nxt = mid;
                    high = mid;
                } else {
                    low = mid + 1;
                }
            }

            for (int k = 1; k <= 4; ++k) {
                // Choice 1: Skip the current interval
                State skip = dp[i + 1][k];
                // Choice 2: Take the current interval
                State tk = takeState(arr[i].w, arr[i].id, dp[nxt][k - 1]);
                
                // Store whichever yields a better overall result
                if (isBetter(tk, skip)) {
                    dp[i][k] = tk;
                } else {
                    dp[i][k] = skip;
                }
            }
        }

        // Translate the final optimal state to a vector mapping
        vector<int> result;
        for (int i = 0; i < dp[0][4].count; ++i) {
            result.push_back(dp[0][4].ids[i]);
        }
        
        return result;
    }
};