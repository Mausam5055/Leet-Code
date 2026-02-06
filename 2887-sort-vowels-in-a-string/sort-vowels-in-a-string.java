import java.util.*;

class Solution {
    public String sortVowels(String s) {
        Set<Character> vowelsSet = new HashSet<>(
            Arrays.asList('a','e','i','o','u','A','E','I','O','U')
        );

        List<Character> vowels = new ArrayList<>();

        // Step 1: Collect vowels
        for (char c : s.toCharArray()) {
            if (vowelsSet.contains(c)) {
                vowels.add(c);
            }
        }

        // Step 2: Sort vowels by ASCII
        Collections.sort(vowels);

        // Step 3: Rebuild string
        StringBuilder result = new StringBuilder();
        int idx = 0;

        for (char c : s.toCharArray()) {
            if (vowelsSet.contains(c)) {
                result.append(vowels.get(idx++));
            } else {
                result.append(c);
            }
        }

        return result.toString();
    }
}
