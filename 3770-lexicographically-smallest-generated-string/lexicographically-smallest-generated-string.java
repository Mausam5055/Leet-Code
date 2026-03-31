import java.util.*;

class Solution {
    public String generateString(String str1, String str2) {
        int n = str1.length();
        int m = str2.length();

        char[] word = new char[n + m - 1];
        Arrays.fill(word, 'a');

        // Track positions fixed by 'T'
        boolean[] locked = new boolean[n + m - 1];

        // Step 1: Apply 'T' constraints
        for (int i = 0; i < n; i++) {
            if (str1.charAt(i) == 'T') {
                for (int j = 0; j < m; j++) {
                    if (word[i + j] != 'a' && word[i + j] != str2.charAt(j)) {
                        return ""; // conflict
                    }
                    word[i + j] = str2.charAt(j);
                    locked[i + j] = true;
                }
            }
        }

        // Step 2: Handle 'F' constraints
        for (int i = 0; i < n; i++) {
            if (str1.charAt(i) == 'F') {

                // Check if currently equal to str2
                boolean match = true;
                for (int j = 0; j < m; j++) {
                    if (word[i + j] != str2.charAt(j)) {
                        match = false;
                        break;
                    }
                }

                // If equal, we must break it
                if (match) {
                    boolean changed = false;

                    // Try to change from right to left (keeps lexicographically small)
                    for (int j = m - 1; j >= 0; j--) {
                        int pos = i + j;

                        if (locked[pos]) continue; // cannot modify T-fixed positions

                        // Try smallest possible different char
                        for (char c = 'a'; c <= 'z'; c++) {
                            if (c != str2.charAt(j)) {
                                word[pos] = c;
                                changed = true;
                                break;
                            }
                        }

                        if (changed) break;
                    }

                    if (!changed) return ""; // impossible
                }
            }
        }

        // Step 3: Final validation (VERY IMPORTANT)
        for (int i = 0; i < n; i++) {
            boolean match = true;

            for (int j = 0; j < m; j++) {
                if (word[i + j] != str2.charAt(j)) {
                    match = false;
                    break;
                }
            }

            if (str1.charAt(i) == 'T' && !match) return "";
            if (str1.charAt(i) == 'F' && match) return "";
        }

        return new String(word);
    }
}