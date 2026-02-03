class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size()) return "";

        unordered_map<char, int> need, window;
        for (char c : t) need[c]++;

        int required = need.size();
        int formed = 0;

        int l = 0, r = 0;
        int minLen = INT_MAX;
        int start = 0;

        while (r < s.size()) {
            char c = s[r];
            window[c]++;

            if (need.count(c) && window[c] == need[c]) {
                formed++;
            }

            // Try to shrink
            while (l <= r && formed == required) {
                if (r - l + 1 < minLen) {
                    minLen = r - l + 1;
                    start = l;
                }

                char leftChar = s[l];
                window[leftChar]--;

                if (need.count(leftChar) && window[leftChar] < need[leftChar]) {
                    formed--;
                }
                l++;
            }
            r++;
        }

        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};
