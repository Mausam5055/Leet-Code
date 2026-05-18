class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();

        // Edge case
        if (n == 1)
            return 0;

        // Store all indices for each value
        unordered_map<int, vector<int>> mp;

        for (int i = 0; i < n; i++) {
            mp[arr[i]].push_back(i);
        }

        // BFS
        queue<int> q;
        vector<bool> visited(n, false);

        q.push(0);
        visited[0] = true;

        int steps = 0;

        while (!q.empty()) {

            int size = q.size();

            while (size--) {

                int curr = q.front();
                q.pop();

                // Reached last index
                if (curr == n - 1)
                    return steps;

                // Store neighbors
                vector<int> nextIndices;

                // Same value jumps
                for (int idx : mp[arr[curr]]) {
                    nextIndices.push_back(idx);
                }

                // i + 1
                if (curr + 1 < n)
                    nextIndices.push_back(curr + 1);

                // i - 1
                if (curr - 1 >= 0)
                    nextIndices.push_back(curr - 1);

                // Visit neighbors
                for (int next : nextIndices) {

                    if (!visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }

                // Important optimization
                mp[arr[curr]].clear();
            }

            steps++;
        }

        return -1;
    }
};