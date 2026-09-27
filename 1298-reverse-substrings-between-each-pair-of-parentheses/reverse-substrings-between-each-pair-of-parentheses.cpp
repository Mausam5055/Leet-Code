#include <string>
#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    string reverseParentheses(string s) {
        int n = s.length();
        vector<int> pair(n);
        stack<int> st;
        
        // Step 1: Precompute matching parentheses indices
        for (int i = 0; i < n; ++i) {
            if (s[i] == '(') {
                st.push(i);
            } else if (s[i] == ')') {
                int j = st.top();
                st.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }
        
        // Step 2: Traverse string with direction toggling
        string result = "";
        int i = 0;
        int direction = 1; // 1 for forward, -1 for backward
        
        while (i < n) {
            if (s[i] == '(' || s[i] == ')') {
                // Teleport to the matching parenthesis and reverse direction
                i = pair[i];
                direction = -direction;
            } else {
                result += s[i];
            }
            i += direction;
        }
        
        return result;
    }
};