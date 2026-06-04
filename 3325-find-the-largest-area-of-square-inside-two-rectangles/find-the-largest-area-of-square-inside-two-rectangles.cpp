class Solution {
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft,
                                vector<vector<int>>& topRight) {

        int n = bottomLeft.size();
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {

                long long w = min(topRight[i][0], topRight[j][0]) -
                              max(bottomLeft[i][0], bottomLeft[j][0]);

                long long h = min(topRight[i][1], topRight[j][1]) -
                              max(bottomLeft[i][1], bottomLeft[j][1]);

                long long side = min(w, h);

                if (side > 0) {
                    ans = max(ans, side * side);
                }
            }
        }

        return ans;
    }
};