class Solution {
    public int maxFrequencyElements(int[] nums) {

        int[] freq = new int[101];  // nums[i] <= 100

        // Count frequency
        for (int n : nums) {
            freq[n]++;
        }

        // Find maximum frequency
        int maxFreq = 0;
        for (int f : freq) {
            maxFreq = Math.max(maxFreq, f);
        }

        // Sum all frequencies equal to maxFreq
        int result = 0;
        for (int f : freq) {
            if (f == maxFreq) {
                result += f;
            }
        }

        return result;
    }
}
