import java.util.*;

class Solution {
    public String sortVowels(String s) {
        // 1. Collect all vowels from the string
        List<Character> vowels = new ArrayList<>();
        for (char c : s.toCharArray()) {
            if (isVowel(c)) {
                vowels.add(c);
            }
        }
        
        // 2. Sort the vowels by ASCII value
        Collections.sort(vowels);
        
        // 3. Reconstruct the string
        StringBuilder result = new StringBuilder();
        int vowelIndex = 0;
        
        for (char c : s.toCharArray()) {
            if (isVowel(c)) {
                // Place the next sorted vowel
                result.append(vowels.get(vowelIndex++));
            } else {
                // Place the original consonant
                result.append(c);
            }
        }
        
        return result.toString();
    }
    
    // Helper method to check if a char is a vowel
    private boolean isVowel(char c) {
        return "aeiouAEIOU".indexOf(c) != -1;
    }
}