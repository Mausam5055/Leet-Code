class Solution {
    public int uniqueXorTriplets(int[] nums) {
        int n = nums.length;

        if (n < 3) return n;

        // Find the Most Significant Bit
        int cnt = 0;
        int temp = n;
        while (temp > 0) {
            temp >>= 1;
            cnt++;
        }

        return (int)Math.pow(2, cnt);
    }
}