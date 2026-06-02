class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {
        
        int ans = INT_MAX;
        int n = landStartTime.size();
        int m = waterStartTime.size();

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {

                // Land -> Water
                int landFinish = landStartTime[i] + landDuration[i];
                int finish1 = max(landFinish, waterStartTime[j]) + waterDuration[j];
                ans = min(ans, finish1);

                // Water -> Land
                int waterFinish = waterStartTime[j] + waterDuration[j];
                int finish2 = max(waterFinish, landStartTime[i]) + landDuration[i];
                ans = min(ans, finish2);
            }
        }

        return ans;
    }
};