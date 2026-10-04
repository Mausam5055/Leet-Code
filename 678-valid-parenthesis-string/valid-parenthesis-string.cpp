class Solution {
public:
    bool checkValidString(string s) {
        int cmin = 0; // Minimum open '('
        int cmax = 0; // Maximum open '('
        
        for (char c : s) {
            if (c == '(') {
                cmax++;
                cmin++;
            } else if (c == ')') {
                cmax--;
                cmin = max(cmin - 1, 0);
            } else if (c == '*') {
                cmax++; // '*' acts as '('
                cmin = max(cmin - 1, 0); // '*' acts as ')'
            }
            
            // If we ever have more ')' than possible '(' + '*', it's invalid
            if (cmax < 0) {
                return false;
            }
        }
        
        // True if we can have exactly 0 open '(' left
        return cmin == 0; 
    }
};