#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();
        // dp[i] stores the minimum length of a valid subarray ending at or before index i
        vector<int> dp(n, 1e9); 
        
        int left = 0;
        int current_sum = 0;
        int min_len_so_far = 1e9;
        int result = 1e9;

        for (int right = 0; right < n; ++right) {
            current_sum += arr[right];
            
            // Shrink window from the left if the sum exceeds the target
            while (current_sum > target) {
                current_sum -= arr[left];
                left++;
            }
            
            if (current_sum == target) {
                int current_len = right - left + 1;
                
                // If there is a valid subarray before our current window starts
                if (left > 0 && dp[left - 1] != 1e9) {
                    result = min(result, current_len + dp[left - 1]);
                }
                
                // Update the best single subarray length seen so far
                min_len_so_far = min(min_len_so_far, current_len);
            }
            
            // Record the best length found up to the current index
            dp[right] = min_len_so_far;
        }

        return result == 1e9 ? -1 : result;
    }
};