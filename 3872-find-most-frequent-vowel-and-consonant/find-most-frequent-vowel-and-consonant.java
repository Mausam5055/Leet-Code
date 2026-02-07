class Solution {
    // Renamed from maxFreq to maxFreqSum to match LeetCode's expected interface
    public int maxFreqSum(String s) {
        int[] freq = new int[26];
        
        // 1. Count frequencies of all characters
        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }
        
        int maxVowel = 0;
        int maxConsonant = 0;
        
        // 2. Iterate through 'a' to 'z' to find maxes
        for (int i = 0; i < 26; i++) {
            char c = (char) (i + 'a');
            int count = freq[i];
            
            if (count > 0) { // Only consider present characters
                if (isVowel(c)) {
                    maxVowel = Math.max(maxVowel, count);
                } else {
                    maxConsonant = Math.max(maxConsonant, count);
                }
            }
        }
        
        return maxVowel + maxConsonant;
    }
    
    private boolean isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
}