#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestAltitude(vector<int>& gain) {
        int current_altitude = 0;
        int max_altitude = 0;
        
        for (int g : gain) {
            current_altitude += g;
            max_altitude = max(max_altitude, current_altitude);
        }
        
        return max_altitude;
    }
};