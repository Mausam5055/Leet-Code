class Solution {
public:
    vector<vector<int>> ans;
    vector<int> curr;
    vector<bool> used;

    void backtrack(vector<int>& nums) {
        if (curr.size() == nums.size()) {
            ans.push_back(curr);
            return;
        }

        for (int i = 0; i < nums.size(); i++) {
            if (used[i]) continue;

            // Skip duplicates
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1])
                continue;

            used[i] = true;
            curr.push_back(nums[i]);

            backtrack(nums);

            curr.pop_back();
            used[i] = false;
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());   // VERY IMPORTANT
        used.assign(nums.size(), false);
        backtrack(nums);
        return ans;
    }
};

