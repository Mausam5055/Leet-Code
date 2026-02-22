class Solution {
    public int binaryGap(int n) {
        int lastIndex = -1;
        int maxDist = 0;
        int index = 0;

        while (n > 0) {
            if ((n & 1) == 1) {  // current bit is 1
                if (lastIndex != -1) {
                    maxDist = Math.max(maxDist, index - lastIndex);
                }
                lastIndex = index;
            }
            n >>= 1;  // shift right
            index++;
        }

        return maxDist;
    }
}