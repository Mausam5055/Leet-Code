class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {

        vector<int> ans;

        for (int num : nums) {

            // Even number impossible
            if (num == 2) {
                ans.push_back(-1);
                continue;
            }

            int x = num;

            // Find first 0 bit
            for (int bit = 0; bit < 31; bit++) {

                if (((num >> bit) & 1) == 0) {

                    // Unset previous bit
                    x = num ^ (1 << (bit - 1));
                    break;
                }
            }

            ans.push_back(x);
        }

        return ans;
    }
};