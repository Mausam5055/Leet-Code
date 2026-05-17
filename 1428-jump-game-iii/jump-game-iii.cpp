class Solution {
public:
    bool dfs(vector<int>& arr, int idx, vector<bool>& visited) {
        
        // Out of bounds
        if (idx < 0 || idx >= arr.size())
            return false;

        // Already visited
        if (visited[idx])
            return false;

        // Found zero
        if (arr[idx] == 0)
            return true;

        visited[idx] = true;

        // Jump forward or backward
        return dfs(arr, idx + arr[idx], visited) ||
               dfs(arr, idx - arr[idx], visited);
    }

    bool canReach(vector<int>& arr, int start) {
        vector<bool> visited(arr.size(), false);

        return dfs(arr, start, visited);
    }
};