#include <vector>
#include <numeric>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> leftRightDifference(vector<int>& nums) {
        int n = nums.size();
        vector<int> answer(n);
        
        int leftSum = 0;
        int rightSum = 0;
        
        // Calculate the initial rightSum (total sum of the array)
        for (int num : nums) {
            rightSum += num;
        }
        
        // Traverse the array to calculate the differences
        for (int i = 0; i < n; ++i) {
            // Remove the current element from rightSum
            rightSum -= nums[i];
            
            // Calculate absolute difference
            answer[i] = abs(leftSum - rightSum);
            
            // Add the current element to leftSum for the next index
            leftSum += nums[i];
        }
        
        return answer;
    }
};