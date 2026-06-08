#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid) {
        int m = boxGrid.size();
        int n = boxGrid[0].size();
        
        // Step 1: Apply gravity (shift stones to the right)
        for (int i = 0; i < m; ++i) {
            int empty = n - 1; // The rightmost available position
            for (int j = n - 1; j >= 0; --j) {
                if (boxGrid[i][j] == '*') {
                    // Obstacle found, next available spot is just left of it
                    empty = j - 1;
                } else if (boxGrid[i][j] == '#') {
                    // Stone found, move it to the 'empty' position
                    // We only swap if the stone actually needs to fall
                    if (empty != j) {
                        boxGrid[i][empty] = '#';
                        boxGrid[i][j] = '.';
                    }
                    empty--;
                }
            }
        }
        
        // Step 2: Rotate the grid 90 degrees clockwise
        vector<vector<char>> rotatedBox(n, vector<char>(m));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // Original (i, j) maps to Rotated (j, m - 1 - i)
                rotatedBox[j][m - 1 - i] = boxGrid[i][j];
            }
        }
        
        return rotatedBox;
    }
};