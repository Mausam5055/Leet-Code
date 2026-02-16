class Solution {
    public int reverseBits(int n) {
        int result = 0;
        
        for (int i = 0; i < 32; i++) {
            result <<= 1;          // make space on right
            result |= (n & 1);     // copy last bit of n
            n >>= 1;               // move to next bit
        }
        
        return result;
    }
}
