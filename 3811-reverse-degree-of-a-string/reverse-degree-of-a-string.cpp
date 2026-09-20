class Solution {
public:
    int reverseDegree(string s) {
        int total_degree = 0;
        
        for (int i = 0; i < s.length(); i++) {
            // Calculate reversed alphabet position ('a' = 26, ..., 'z' = 1)
            int rev_alpha_pos = 26 - (s[i] - 'a');
            
            // Calculate 1-indexed position in the string
            int str_pos = i + 1;
            
            // Add the product to the total sum
            total_degree += rev_alpha_pos * str_pos;
        }
        
        return total_degree;
    }
};