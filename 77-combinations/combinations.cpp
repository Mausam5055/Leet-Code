class Solution {
public:
    vector<vector<int>> result;
    vector<int> path;

    void backtrack(int start, int n, int k) {
        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        for (int i = start; i <= n - (k - path.size()) + 1; i++) {
            path.push_back(i);
            backtrack(i + 1, n, k);
            path.pop_back(); // backtrack
        }
    }

    vector<vector<int>> combine(int n, int k) {
        backtrack(1, n, k);
        return result;
    }
};
