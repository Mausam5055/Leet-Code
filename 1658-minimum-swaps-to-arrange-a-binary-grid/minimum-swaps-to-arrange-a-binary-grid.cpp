class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<int> trailingZeros(n, 0);
        
        // Step 1: Count trailing zeros for each row
        for (int i = 0; i < n; ++i) {
            int count = 0;
            // Start from the end of the row and count backwards
            for (int j = n - 1; j >= 0; --j) {
                if (grid[i][j] == 0) {
                    count++;
                } else {
                    break; // Stop at the first '1' encountered
                }
            }
            trailingZeros[i] = count;
        }
        
        int swaps = 0;
        
        // Step 2: Greedily arrange rows to satisfy the diagonal condition
        for (int i = 0; i < n; ++i) {
            int targetZeros = n - 1 - i;
            int j = i;
            
            // Find the closest row 'j' that has enough trailing zeros
            while (j < n && trailingZeros[j] < targetZeros) {
                j++;
            }
            
            // If no valid row is found below or at 'i', it's impossible
            if (j == n) {
                return -1;
            }
            
            // Step 3: Simulate adjacent swaps to bring row 'j' up to row 'i'
            int foundZeros = trailingZeros[j];
            while (j > i) {
                trailingZeros[j] = trailingZeros[j - 1]; // Shift row down
                j--;
                swaps++; // Each shift is one adjacent swap
            }
            // Place the found valid row at its correct position 'i'
            trailingZeros[i] = foundZeros;
        }
        
        return swaps;
    }
};