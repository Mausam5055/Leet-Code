class Solution {
public:
    vector<vector<int>> ans;
    vector<int> temp;

    void backtrack(vector<int>& candidates, int target, int index) {
        // Base case: exact target achieved
        if (target == 0) {
            ans.push_back(temp);
            return;
        }

        // If target becomes negative, stop exploring
        if (target < 0) return;

        // Try all candidates starting from current index
        for (int i = index; i < candidates.size(); i++) {
            temp.push_back(candidates[i]);
            backtrack(candidates, target - candidates[i], i); // reuse allowed
            temp.pop_back(); // backtrack
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        backtrack(candidates, target, 0);
        return ans;
    }
};
