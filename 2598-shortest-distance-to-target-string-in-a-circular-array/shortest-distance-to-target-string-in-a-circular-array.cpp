class Solution {
public:
    int closestTarget(vector<string>& words, string target, int startIndex) {

        int n = words.size();
        int ans = INT_MAX;

        for (int i = 0; i < n; i++) {

            if (words[i] == target) {

                int direct = abs(i - startIndex);
                int circular = n - direct;

                ans = min(ans, min(direct, circular));
            }
        }

        return (ans == INT_MAX) ? -1 : ans;
    }
};