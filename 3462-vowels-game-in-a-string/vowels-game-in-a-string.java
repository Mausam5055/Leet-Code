class Solution {
    public boolean doesAliceWin(String s) {
        // The logic simplifies to: 
        // If there is at least one vowel, Alice can force a win.
        // If there are no vowels, Alice has no valid opening move.
        
        for (char c : s.toCharArray()) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                return true;
            }
        }
        
        return false;
    }
}