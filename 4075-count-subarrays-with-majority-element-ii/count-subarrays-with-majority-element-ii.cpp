#include <vector>

using namespace std;

class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();
        // The prefix sum can range from -n to n.
        // We shift the index by n + 1 to make it strictly 1-indexed for the Fenwick Tree.
        vector<int> bit(2 * n + 2, 0);
        
        // Function to add a value to the Binary Indexed Tree
        auto add = [&](int idx, int val) {
            for (; idx <= 2 * n + 1; idx += idx & -idx) {
                bit[idx] += val;
            }
        };
        
        // Function to get the prefix sum from the Binary Indexed Tree
        auto query = [&](int idx) {
            int sum = 0;
            for (; idx > 0; idx -= idx & -idx) {
                sum += bit[idx];
            }
            return sum;
        };
        
        long long ans = 0;
        int current_sum = 0;
        
        // Base case: A prefix sum of 0 before including any elements
        add(0 + n + 1, 1);
        
        for (int i = 0; i < n; ++i) {
            if (nums[i] == target) {
                current_sum += 1; // target contributes +1
            } else {
                current_sum -= 1; // non-target contributes -1
            }
            
            // We want to find how many prefix sums encountered so far are strictly less than current_sum.
            // This is equivalent to querying the prefix sums <= current_sum - 1.
            ans += query(current_sum - 1 + n + 1);
            
            // Update the BIT with the current prefix sum
            add(current_sum + n + 1, 1);
        }
        
        return ans;
    }
};