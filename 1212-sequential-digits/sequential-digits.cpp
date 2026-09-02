class Solution {
public:
    vector<int> sequentialDigits(int low, int high) {
        string digits = "123456789";
        vector<int> result;
        
        // Length of the sequential numbers can range from 2 to 9
        for (int length = 2; length <= 9; length++) {
            // Sliding window starting point
            for (int start = 0; start <= 9 - length; start++) {
                // Extract the substring and convert to integer
                string sub = digits.substr(start, length);
                int num = stoi(sub);
                
                // If it's within bounds, add it to the result
                if (num >= low && num <= high) {
                    result.push_back(num);
                }
            }
        }
        
        return result;
    }
};