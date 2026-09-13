#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        vector<pair<int, int>> ones1, ones2;
        
        // Step 1: Collect coordinates of all 1s
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (img1[i][j] == 1) ones1.push_back({i, j});
                if (img2[i][j] == 1) ones2.push_back({i, j});
            }
        }
        
        unordered_map<int, int> vectorCount;
        int maxOverlap = 0;
        
        // Step 2 & 3: Calculate translation vectors and count their frequencies
        for (auto& p1 : ones1) {
            for (auto& p2 : ones2) {
                int dx = p2.first - p1.first;
                int dy = p2.second - p1.second;
                
                // Encode the 2D vector (dx, dy) into a 1D integer key
                // Since dx and dy range from -29 to 29, shifting by n (30) makes them strictly positive.
                // Multiplying by 100 separates the x and y components safely.
                int key = (dx + n) * 100 + (dy + n); 
                
                vectorCount[key]++;
                maxOverlap = max(maxOverlap, vectorCount[key]);
            }
        }
        
        return maxOverlap;
    }
};