#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int stoneGameVIII(vector<int>& stones) {
        int n = stones.size();
        
        // Calculate the sum of all elements (which is the prefix sum P[n-1])
        int prefixSum = accumulate(stones.begin(), stones.end(), 0);
        
        // Base case: picking all stones
        int maxDiff = prefixSum;
        
        // Traverse backwards from n-2 down to 1
        // Alice must pick at least 2 stones (i >= 1)
        for (int i = n - 2; i >= 1; --i) {
            // Update prefix sum to P[i] by subtracting the element to the right
            prefixSum -= stones[i + 1];
            
            // maxDiff represents dp[i] = max(dp[i+1], P[i] - dp[i+1])
            maxDiff = max(maxDiff, prefixSum - maxDiff);
        }
        
        return maxDiff;
    }
};