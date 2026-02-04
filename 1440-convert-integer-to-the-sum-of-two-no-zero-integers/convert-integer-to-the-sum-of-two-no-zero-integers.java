class Solution {
    public int[] getNoZeroIntegers(int n) {
        // Iterate a from 1 up to n
        for (int a = 1; a < n; a++) {
            int b = n - a;
            
            // Check if both a and b are "No-Zero" integers
            if (!hasZero(a) && !hasZero(b)) {
                return new int[]{a, b};
            }
        }
        return new int[]{}; // Should not be reached per problem constraints
    }

    // Helper method to check if a number contains the digit '0'
    private boolean hasZero(int num) {
        while (num > 0) {
            if (num % 10 == 0) {
                return true; // Found a zero
            }
            num /= 10;
        }
        return false;
    }
}