#include <vector>

using namespace std;

class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        for (int i = 0; i < nums.size(); ++i) {
            int digit_sum = 0;
            int current_num = nums[i];
            
            // Calculate the sum of the digits
            while (current_num > 0) {
                digit_sum += current_num % 10;
                current_num /= 10;
            }
            
            // If the digit sum matches the index, we've found our answer
            if (digit_sum == i) {
                return i;
            }
        }
        
        // If we check every element and find no match
        return -1;
    }
};