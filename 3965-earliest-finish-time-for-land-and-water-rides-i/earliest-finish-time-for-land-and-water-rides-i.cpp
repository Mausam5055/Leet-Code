#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();
        
        int earliest_finish = 2e9; // Initialize with a very large number
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                
                // Scenario 1: Land ride FIRST, then Water ride
                int finish_land_1 = landStartTime[i] + landDuration[i];
                int start_water_1 = max(finish_land_1, waterStartTime[j]);
                int finish_total_1 = start_water_1 + waterDuration[j];
                
                // Scenario 2: Water ride FIRST, then Land ride
                int finish_water_2 = waterStartTime[j] + waterDuration[j];
                int start_land_2 = max(finish_water_2, landStartTime[i]);
                int finish_total_2 = start_land_2 + landDuration[i];
                
                // Update our global earliest finish time
                earliest_finish = min({earliest_finish, finish_total_1, finish_total_2});
            }
        }
        
        return earliest_finish;
    }
};