import java.util.*;

class Solution {
    public List<String> removeAnagrams(String[] words) {
        List<String> result = new ArrayList<>();

        for (String word : words) {
            if (result.isEmpty() || 
                !isAnagram(result.get(result.size() - 1), word)) {
                result.add(word);
            }
        }

        return result;
    }

    private boolean isAnagram(String a, String b) {
        char[] c1 = a.toCharArray();
        char[] c2 = b.toCharArray();

        Arrays.sort(c1);
        Arrays.sort(c2);

        return Arrays.equals(c1, c2);
    }
}