import java.util.*;

class Solution {
    public String[] spellchecker(String[] wordlist, String[] queries) {
        
        Set<String> exactWords = new HashSet<>();
        Map<String, String> caseMap = new HashMap<>();
        Map<String, String> vowelMap = new HashMap<>();
        
        // Preprocess wordlist
        for (String word : wordlist) {
            exactWords.add(word);
            
            String lower = word.toLowerCase();
            caseMap.putIfAbsent(lower, word);
            
            String devowel = devowel(lower);
            vowelMap.putIfAbsent(devowel, word);
        }
        
        String[] result = new String[queries.length];
        
        for (int i = 0; i < queries.length; i++) {
            String q = queries[i];
            
            // 1. Exact match
            if (exactWords.contains(q)) {
                result[i] = q;
                continue;
            }
            
            String lowerQ = q.toLowerCase();
            
            // 2. Case-insensitive match
            if (caseMap.containsKey(lowerQ)) {
                result[i] = caseMap.get(lowerQ);
                continue;
            }
            
            // 3. Vowel-error match
            String devowelQ = devowel(lowerQ);
            if (vowelMap.containsKey(devowelQ)) {
                result[i] = vowelMap.get(devowelQ);
                continue;
            }
            
            // 4. No match
            result[i] = "";
        }
        
        return result;
    }
    
    private String devowel(String word) {
        StringBuilder sb = new StringBuilder();
        for (char c : word.toCharArray()) {
            if (isVowel(c)) sb.append('*');
            else sb.append(c);
        }
        return sb.toString();
    }
    
    private boolean isVowel(char c) {
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    }
}
