class Solution {
    public int numSteps(String s) {
        int steps = 0;
        int carry = 0;

        // Traverse from right to left, ignore MSB (index 0)
        for (int i = s.length() - 1; i > 0; i--) {
            int bit = s.charAt(i) - '0';

            if (bit + carry == 1) {
                // Odd → add 1 (carry=1) then divide
                steps += 2;
                carry = 1;
            } else {
                // Even → divide
                steps += 1;
            }
        }

        // If carry remains at MSB, one extra step needed
        return steps + carry;
    }
}