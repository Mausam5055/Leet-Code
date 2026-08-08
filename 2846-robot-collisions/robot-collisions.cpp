#include <vector>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int n = positions.size();
        
        // Array to keep track of original indices
        vector<int> ids(n);
        iota(ids.begin(), ids.end(), 0); 
        
        // Sort indices based on starting positions from left to right
        sort(ids.begin(), ids.end(), [&](int i, int j) {
            return positions[i] < positions[j];
        });

        vector<int> st; // Stack to hold indices of processed robots
        
        for (int id : ids) {
            if (directions[id] == 'R') {
                // Moving right, no immediate collision, push to stack
                st.push_back(id);
            } else {
                // Moving left, process potential collisions
                while (!st.empty() && directions[st.back()] == 'R' && healths[id] > 0) {
                    int top_id = st.back();
                    
                    if (healths[id] > healths[top_id]) {
                        // Current 'L' robot wins
                        healths[id] -= 1;
                        healths[top_id] = 0; // Top robot is destroyed
                        st.pop_back();
                    } else if (healths[id] < healths[top_id]) {
                        // Top 'R' robot wins
                        healths[top_id] -= 1;
                        healths[id] = 0; // Current robot is destroyed
                    } else {
                        // Tie: both are destroyed
                        healths[id] = 0;
                        healths[top_id] = 0;
                        st.pop_back();
                    }
                }
                
                // If the current 'L' robot survived all collisions, it joins the survivors
                if (healths[id] > 0) {
                    st.push_back(id);
                }
            }
        }
        
        // Collect surviving robots in their original order
        vector<int> result;
        for (int i = 0; i < n; ++i) {
            if (healths[i] > 0) {
                result.push_back(healths[i]);
            }
        }
        
        return result;
    }
};