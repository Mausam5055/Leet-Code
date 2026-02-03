class Solution {
public:
    vector<vector<int>> ans;
    vector<int> temp;

    void backtrack(vector<int>& candidates, int target, int index) {
        // Found a valid combination
        if (target == 0) {
            ans.push_back(temp);
            return;
        }

        for (int i = index; i < candidates.size(); i++) {
            // Skip duplicates at the same recursion level
            if (i > index && candidates[i] == candidates[i - 1])
                continue;

            // If current number exceeds target, no need to continue
            if (candidates[i] > target)
                break;

            temp.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i + 1); // use once
            temp.pop_back(); // backtrack
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        backtrack(candidates, target, 0);
        return ans;
    }
};
