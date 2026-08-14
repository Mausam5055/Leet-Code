#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    int numberOfSpecialChars(string word) {
        // Arrays to store presence of lowercase and uppercase letters
        vector<bool> lower(26, false);
        vector<bool> upper(26, false);
        
        for (char c : word) {
            if (c >= 'a' && c <= 'z') {
                lower[c - 'a'] = true;
            } else if (c >= 'A' && c <= 'Z') {
                upper[c - 'A'] = true;
            }
        }
        
        int special_count = 0;
        
        // Count letters that have both cases present
        for (int i = 0; i < 26; ++i) {
            if (lower[i] && upper[i]) {
                special_count++;
            }
        }
        
        return special_count;
    }
};