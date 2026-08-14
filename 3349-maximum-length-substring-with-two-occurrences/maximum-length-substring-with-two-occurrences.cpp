class Solution {
public:
    int maximumLengthSubstring(string s) {
        int max_len = 0;
        int left = 0;
        int freq[26] = {0}; // To store frequency of lowercase English letters
        
        for (int right = 0; right < s.length(); ++right) {
            // Add the current character to our window
            freq[s[right] - 'a']++;
            
            // If the character count exceeds 2, shrink the window from the left
            while (freq[s[right] - 'a'] > 2) {
                freq[s[left] - 'a']--;
                left++;
            }
            
            // Update the maximum length of the valid window
            max_len = max(max_len, right - left + 1);
        }
        
        return max_len;
    }
};