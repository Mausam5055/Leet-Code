class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        string current;
        backtrack(result, current, 0, 0, n);
        return result;
    }
    
private:
    void backtrack(vector<string>& result, string& current, int open, int close, int n) {
        // Base case: If the current string length is 2*n, it's a valid combination
        if (current.length() == n * 2) {
            result.push_back(current);
            return;
        }
        
        // If we haven't used all open parentheses, we can add one
        if (open < n) {
            current.push_back('(');
            backtrack(result, current, open + 1, close, n);
            current.pop_back(); // backtrack to try the next combination
        }
        
        // If we have more open parentheses than close parentheses, we can add a close one
        if (close < open) {
            current.push_back(')');
            backtrack(result, current, open, close + 1, n);
            current.pop_back(); // backtrack to try the next combination
        }
    }
};