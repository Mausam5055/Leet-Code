class Solution {
public:
    string longestPalindrome(string s) {
        int n = s.size();
        if (n <= 1) return s;

        int start = 0, maxLen = 1;

        auto expand = [&](int left, int right) {
            while (left >= 0 && right < n && s[left] == s[right]) {
                left--;
                right++;
            }
            // left+1 ... right-1 is palindrome
            int len = right - left - 1;
            return pair<int,int>(left + 1, len);
        };

        for (int i = 0; i < n; i++) {
            // odd-length palindromes
            auto [oddStart, oddLen] = expand(i, i);
            if (oddLen > maxLen) {
                start = oddStart;
                maxLen = oddLen;
            }

            // even-length palindromes
            auto [evenStart, evenLen] = expand(i, i + 1);
            if (evenLen > maxLen) {
                start = evenStart;
                maxLen = evenLen;
            }
        }

        return s.substr(start, maxLen);
    }
};
