#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minOperations(string s) {
        int diff_0 = 0;
        int n = s.length();
        
        // Check against the "010101..." pattern
        for (int i = 0; i < n; ++i) {
            // s[i] - '0' converts the char to an integer (0 or 1)
            if (s[i] - '0' != i % 2) {
                diff_0++;
            }
        }
        
        // Return the minimum of changing to "0101..." vs changing to "1010..."
        return min(diff_0, n - diff_0);
    }
};