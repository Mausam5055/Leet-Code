#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> hashmap; // value -> index
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            if (hashmap.find(complement) != hashmap.end()) {
                return {hashmap[complement], i};
            }
            
            hashmap[nums[i]] = i;
        }
        
        return {}; // not needed as per constraints, but good practice
    }
};
