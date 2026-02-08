class Solution {
    public boolean doesAliceWin(String s) {
        for (char c : s.toCharArray()) {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                return true;  // Alice can make at least one move
            }
        }
        return false; // No vowels → Alice loses immediately
    }
}
