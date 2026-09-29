#include <vector>

using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        // A valid parentheses string must be of even length
        if ((m + n - 1) % 2 != 0) {
            return false;
        }
        
        // If the grid starts with a closing bracket or ends with an opening one, it's invalid
        if (grid[0][0] == ')' || grid[m-1][n-1] == '(') {
            return false;
        }
        
        // The maximum possible balance we could have at any point is half the total path length
        int max_bal = (m + n) / 2;
        
        // visited[r][c][bal] tracks if we have already visited cell (r, c) with `bal` balance
        vector<vector<vector<bool>>> visited(m, vector<vector<bool>>(n, vector<bool>(max_bal + 1, false)));
        
        return dfs(0, 0, 0, grid, visited, m, n);
    }
    
private:
    bool dfs(int r, int c, int bal, vector<vector<char>>& grid, vector<vector<vector<bool>>>& visited, int m, int n) {
        // Update balance
        bal += (grid[r][c] == '(' ? 1 : -1);
        
        // Invalid path if balance drops below zero
        if (bal < 0) return false;
        
        // Pruning: if the current balance exceeds the number of steps left, we can't close all brackets
        int remaining_steps = (m - 1 - r) + (n - 1 - c);
        if (bal > remaining_steps) return false;
        
        // If we reached the destination
        if (r == m - 1 && c == n - 1) {
            return bal == 0;
        }
        
        // If we have already explored this exact state and it returned false, skip it
        if (visited[r][c][bal]) return false;
        
        // Mark as visited (since we only care if it succeeds, marking it true means we explored it and it failed)
        visited[r][c][bal] = true;
        
        // Explore downwards and rightwards
        if (r + 1 < m && dfs(r + 1, c, bal, grid, visited, m, n)) return true;
        if (c + 1 < n && dfs(r, c + 1, bal, grid, visited, m, n)) return true;
        
        return false;
    }
};