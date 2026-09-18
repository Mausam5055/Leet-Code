#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Helper function to validate and expand an interval starting at index 'i'
    int getValidRightBoundary(const string& s, int i, const vector<int>& first, const vector<int>& last) {
        int right = last[s[i] - 'a'];
        
        for (int j = i; j <= right; ++j) {
            // If a character inside the range starts before 'i', 
            // a valid interval cannot start exactly at 'i'.
            if (first[s[j] - 'a'] < i) {
                return -1; 
            }
            // Expand the right boundary if the current character ends later
            right = max(right, last[s[j] - 'a']);
        }
        return right;
    }

    vector<string> maxNumOfSubstrings(string s) {
        int n = s.length();
        vector<int> first(26, -1), last(26, -1);
        
        // Step 1: Record the first and last occurrence of each character
        for (int i = 0; i < n; ++i) {
            if (first[s[i] - 'a'] == -1) {
                first[s[i] - 'a'] = i;
            }
            last[s[i] - 'a'] = i;
        }

        // Step 2: Find all valid intervals
        // We store them as {end, start} so they naturally sort by end time
        vector<pair<int, int>> intervals; 
        for (int i = 0; i < 26; ++i) {
            if (first[i] != -1) {
                int left = first[i];
                int right = getValidRightBoundary(s, left, first, last);
                if (right != -1) {
                    intervals.push_back({right, left}); 
                }
            }
        }

        // Step 3: Greedily pick non-overlapping intervals ending earliest
        sort(intervals.begin(), intervals.end());

        vector<string> res;
        int last_end = -1;
        
        for (auto& interval : intervals) {
            int right = interval.first;
            int left = interval.second;
            
            // If this interval doesn't overlap with the previously picked one
            if (left > last_end) {
                res.push_back(s.substr(left, right - left + 1));
                last_end = right;
            }
        }

        return res;
    }
};