import java.util.*;

class Solution {
    public int minimumTeachings(int n, int[][] languages, int[][] friendships) {
        int m = languages.length;
        
        // 1. Precompute languages for fast lookup (O(1))
        // userLanguages[i][j] is true if user i+1 knows language j
        boolean[][] userLanguages = new boolean[m + 1][n + 1];
        for (int i = 0; i < m; i++) {
            for (int lang : languages[i]) {
                userLanguages[i + 1][lang] = true;
            }
        }

        // 2. Identify users in friendships that cannot communicate
        Set<Integer> usersInBadFriendships = new HashSet<>();
        for (int[] f : friendships) {
            int u = f[0];
            int v = f[1];
            
            if (!canCommunicate(u, v, n, userLanguages)) {
                usersInBadFriendships.add(u);
                usersInBadFriendships.add(v);
            }
        }

        // If everyone can already communicate, we teach 0 people
        if (usersInBadFriendships.isEmpty()) {
            return 0;
        }

        // 3. Find the language known by the most users in this subset
        Map<Integer, Integer> langFrequency = new HashMap<>();
        for (int user : usersInBadFriendships) {
            for (int l = 1; l <= n; l++) {
                if (userLanguages[user][l]) {
                    langFrequency.put(l, langFrequency.getOrDefault(l, 0) + 1);
                }
            }
        }

        int maxKnown = 0;
        for (int count : langFrequency.values()) {
            maxKnown = Math.max(maxKnown, count);
        }

        // 4. Result is total problematic users minus those who already know the best language
        return usersInBadFriendships.size() - maxKnown;
    }

    // Helper to check if two users share any language
    private boolean canCommunicate(int u, int v, int n, boolean[][] userLanguages) {
        for (int i = 1; i <= n; i++) {
            if (userLanguages[u][i] && userLanguages[v][i]) {
                return true;
            }
        }
        return false;
    }
}