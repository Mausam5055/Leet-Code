import java.util.*;

class Solution {
    public int minimumTeachings(int n, int[][] languages, int[][] friendships) {
        int m = languages.length;
        
        // Step 1: Build quick lookup table
        boolean[][] knows = new boolean[m + 1][n + 1];
        for (int i = 0; i < m; i++) {
            for (int lang : languages[i]) {
                knows[i + 1][lang] = true;
            }
        }
        
        // Step 2: Find users involved in friendships that cannot communicate
        Set<Integer> needHelp = new HashSet<>();
        
        for (int[] f : friendships) {
            int u = f[0], v = f[1];
            boolean canTalk = false;
            
            for (int lang = 1; lang <= n; lang++) {
                if (knows[u][lang] && knows[v][lang]) {
                    canTalk = true;
                    break;
                }
            }
            
            if (!canTalk) {
                needHelp.add(u);
                needHelp.add(v);
            }
        }
        
        // If everyone can already communicate
        if (needHelp.isEmpty()) return 0;
        
        int answer = Integer.MAX_VALUE;
        
        // Step 3: Try teaching each language
        for (int lang = 1; lang <= n; lang++) {
            int teachCount = 0;
            
            for (int user : needHelp) {
                if (!knows[user][lang]) {
                    teachCount++;
                }
            }
            
            answer = Math.min(answer, teachCount);
        }
        
        return answer;
    }
}
