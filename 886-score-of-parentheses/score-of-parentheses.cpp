class Solution {
public:
    int scoreOfParentheses(string s) {
        int score = 0;
        int depth = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            if (s[i] == '(') {
                depth++;
            } else {
                depth--;
                // If it's a closed parenthesis directly following an open one, it's a "core" ()
                if (s[i - 1] == '(') {
                    score += (1 << depth); // 1 << depth is equivalent to 2^depth
                }
            }
        }
        
        return score;
    }
};