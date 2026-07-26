#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        // Find the minimum worker time to calculate a reasonable upper bound
        long long min_wt = *min_element(workerTimes.begin(), workerTimes.end());
        long long L = 1;
        long long mh = mountainHeight;
        
        // Worst-case scenario: the fastest worker reduces the entire mountain alone
        long long R = min_wt * mh * (mh + 1) / 2;
        long long ans = R;
        
        // Lambda function to check if time T is enough
        auto check = [&](long long T) {
            long long total_reduced = 0;
            
            for (int wt : workerTimes) {
                // We need to find the max x such that x*(x+1) <= 2*T/wt
                long long val = (2LL * T) / wt;
                long long x = sqrt(val);
                
                // Adjust x to avoid precision issues with sqrt
                while (x * (x + 1) > val) {
                    x--;
                }
                while ((x + 1) * (x + 2) <= val) {
                    x++;
                }
                
                total_reduced += x;
                
                // If we've already met the mountain height requirement, time T is sufficient
                if (total_reduced >= mountainHeight) {
                    return true;
                }
            }
            return false;
        };
        
        // Binary Search
        while (L <= R) {
            long long mid = L + (R - L) / 2;
            
            if (check(mid)) {
                ans = mid;     // mid is possible, record it
                R = mid - 1;   // Try to find a smaller sufficient time
            } else {
                L = mid + 1;   // mid is not enough, increase the time
            }
        }
        
        return ans;
    }
};