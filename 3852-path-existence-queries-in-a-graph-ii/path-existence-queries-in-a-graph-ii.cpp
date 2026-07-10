class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        sort(arr.begin(), arr.end());

        vector<int> comp(n), pos(n);
        int cid = 0;

        comp[arr[0].second] = cid;
        pos[arr[0].second] = 0;

        // Group into connected components
        for(int i = 1; i < n; i++) {
            if(arr[i].first - arr[i-1].first > maxDiff) {
                cid++;
            }
            comp[arr[i].second] = cid;
            pos[arr[i].second] = i;
        }

        // up[i][k] stores the furthest sorted index reachable from index i in 2^k jumps
        vector<vector<int>> up(n, vector<int>(20));
        
        int r = 0;
        // Base case: furthest we can reach in 2^0 = 1 jump
        for(int i = 0; i < n; i++) {
            while(r + 1 < n && arr[r + 1].first - arr[i].first <= maxDiff) {
                r++;
            }
            up[i][0] = r;
        }

        // Fill the binary lifting table
        for(int k = 1; k < 20; k++) {
            for(int i = 0; i < n; i++) {
                up[i][k] = up[up[i][k-1]][k-1];
            }
        }

        vector<int> ans;
        for(auto &q : queries) {
            int u = q[0], v = q[1];
            
            // If it's the exact same node, 0 jumps needed
            if (u == v) {
                ans.push_back(0);
                continue;
            }
            // If they are isolated in different components, path is impossible
            if(comp[u] != comp[v]) {
                ans.push_back(-1);
                continue;
            }

            int p1 = pos[u];
            int p2 = pos[v];
            
            // We always jump from the smaller value (left) to larger value (right)
            if (p1 > p2) swap(p1, p2);

            int steps = 0;
            // Greedily jump forward as far as possible without reaching/passing p2
            for (int k = 19; k >= 0; k--) {
                if (up[p1][k] < p2) {
                    p1 = up[p1][k];
                    steps += (1 << k);
                }
            }
            // After the loop, p1 is just shy of p2. One more jump will bridge the gap.
            steps++;
            ans.push_back(steps);
        }

        return ans;
    }
};