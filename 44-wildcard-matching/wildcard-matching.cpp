class Solution {
public:
    bool isMatch(string s, string p) {
        int i = 0, j = 0;
        int starIdx = -1;
        int matchIdx = 0;

        while (i < s.length()) {
            // Case 1: exact match or '?'
            if (j < p.length() && (p[j] == s[i] || p[j] == '?')) {
                i++;
                j++;
            }
            // Case 2: '*'
            else if (j < p.length() && p[j] == '*') {
                starIdx = j;
                matchIdx = i;
                j++;
            }
            // Case 3: mismatch but previous '*'
            else if (starIdx != -1) {
                j = starIdx + 1;
                matchIdx++;
                i = matchIdx;
            }
            // Case 4: mismatch and no '*'
            else {
                return false;
            }
        }

        // Remaining characters in pattern must be '*'
        while (j < p.length() && p[j] == '*') {
            j++;
        }

        return j == p.length();
    }
};
