#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function to check if a substring is a palindrome
    bool isPalindrome(const string& s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

public:
    int maxPalindromes(string s, int k) {
        int n = s.length();
        
        // dp[i] stores the max number of valid palindromes in the prefix s[0...i-1]
        vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= n; ++i) {
            // By default, we don't form a new palindrome ending at i-1
            dp[i] = dp[i - 1];
            
            // Check if there is a palindrome of length k ending at i-1
            if (i >= k && isPalindrome(s, i - k, i - 1)) {
                dp[i] = max(dp[i], dp[i - k] + 1);
            }
            
            // Check if there is a palindrome of length k+1 ending at i-1
            if (i >= k + 1 && isPalindrome(s, i - k - 1, i - 1)) {
                dp[i] = max(dp[i], dp[i - k - 1] + 1);
            }
        }
        
        return dp[n];
    }
};