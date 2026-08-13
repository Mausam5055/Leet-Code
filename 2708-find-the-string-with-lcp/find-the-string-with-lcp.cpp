#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();
        string word(n, ' ');
        char currentChar = 'a';
        
        // Step 1: Greedily construct the lexicographically smallest string
        for (int i = 0; i < n; ++i) {
            if (word[i] == ' ') {
                if (currentChar > 'z') {
                    return ""; // More than 26 distinct characters needed
                }
                for (int j = i; j < n; ++j) {
                    if (lcp[i][j] > 0) {
                        word[j] = currentChar;
                    }
                }
                currentChar++;
            }
        }
        
        // Step 2: Validate the constructed string against the given LCP matrix
        // We traverse backwards to use the already validated lcp[i+1][j+1] state natively
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int expectedLcp = 0;
                
                if (word[i] == word[j]) {
                    if (i + 1 < n && j + 1 < n) {
                        expectedLcp = lcp[i + 1][j + 1] + 1;
                    } else {
                        expectedLcp = 1; // Out of bounds means suffix length is exactly 1
                    }
                }
                
                if (lcp[i][j] != expectedLcp) {
                    return ""; // Found a contradiction, matrix is invalid
                }
            }
        }
        
        return word;
    }
};