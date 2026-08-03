class Solution {
public:
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> pos;

        for (int i = 0; i < nums.size(); i++)
            pos[nums[i]].push_back(i);

        int ans = INT_MAX;

        for (auto &p : pos) {
            vector<int> &v = p.second;

            if (v.size() < 3)
                continue;

            for (int i = 0; i + 2 < v.size(); i++) {
                ans = min(ans, 2 * (v[i + 2] - v[i]));
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};