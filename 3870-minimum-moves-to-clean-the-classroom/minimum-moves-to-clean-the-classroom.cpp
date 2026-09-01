#include <vector>
#include <string>
#include <queue>
#include <tuple>

using namespace std;

class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int start_r = -1, start_c = -1;
        int litter_count = 0;
        
        // Map to quickly find the bit index for each litter item
        vector<vector<int>> litter_id(m, vector<int>(n, -1));
        
        // Find starting position and assign an ID to each litter
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    start_r = i;
                    start_c = j;
                } else if (classroom[i][j] == 'L') {
                    litter_id[i][j] = litter_count++;
                }
            }
        }
        
        int target_mask = (1 << litter_count) - 1;
        
        // max_energy[row][col][mask] stores the max energy we've had at this state
        // Initialized to -1 (meaning unvisited)
        vector<vector<vector<int>>> max_energy(
            m, vector<vector<int>>(n, vector<int>(1 << litter_count, -1))
        );
        
        // queue for BFS: {r, c, mask, current_energy}
        queue<tuple<int, int, int, int>> q;
        
        q.push({start_r, start_c, 0, energy});
        max_energy[start_r][start_c][0] = energy;
        
        int moves = 0;
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            int size = q.size();
            
            // Process layer by layer (level order traversal)
            for (int i = 0; i < size; ++i) {
                auto [r, c, mask, e] = q.front();
                q.pop();
                
                // If we've collected all litter, return the current move count
                if (mask == target_mask) {
                    return moves;
                }
                
                // Cannot make further moves if energy is 0
                if (e == 0) continue;
                
                for (int d = 0; d < 4; ++d) {
                    int nr = r + dr[d];
                    int nc = c + dc[d];
                    
                    // Check bounds and obstacles
                    if (nr >= 0 && nr < m && nc >= 0 && nc < n && classroom[nr][nc] != 'X') {
                        int ne = e - 1;
                        if (ne < 0) continue; 
                        
                        // Step onto Reset Area
                        if (classroom[nr][nc] == 'R') {
                            ne = energy;
                        }
                        
                        // Collect Litter (if it exists here)
                        int nmask = mask;
                        if (classroom[nr][nc] == 'L') {
                            nmask |= (1 << litter_id[nr][nc]);
                        }
                        
                        // Only push to queue if this path offers strictly better energy
                        if (ne > max_energy[nr][nc][nmask]) {
                            max_energy[nr][nc][nmask] = ne;
                            q.push({nr, nc, nmask, ne});
                        }
                    }
                }
            }
            moves++;
        }
        
        return -1; // Path impossible
    }
};