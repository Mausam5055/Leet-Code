class Solution {

    int dist(int a, int b) {
        if (a == -1) return 0;
        int x1 = a / 6, y1 = a % 6;
        int x2 = b / 6, y2 = b % 6;
        return Math.abs(x1 - x2) + Math.abs(y1 - y2);
    }

    public int minimumDistance(String word) {
        int n = word.length();
        
        int[] dp = new int[26];
        for (int i = 0; i < 26; i++) dp[i] = 0; // ✅ FIX

        for (int i = 1; i < n; i++) {
            int curr = word.charAt(i) - 'A';
            int prev = word.charAt(i - 1) - 'A';

            int[] newDp = new int[26];
            for (int j = 0; j < 26; j++) newDp[j] = Integer.MAX_VALUE;

            for (int j = 0; j < 26; j++) {
                // Case 1: same finger
                int cost1 = dp[j] + dist(prev, curr);
                newDp[j] = Math.min(newDp[j], cost1);

                // Case 2: other finger
                int cost2 = dp[j] + dist(j, curr);
                newDp[prev] = Math.min(newDp[prev], cost2);
            }

            dp = newDp;
        }

        int ans = Integer.MAX_VALUE;
        for (int x : dp) ans = Math.min(ans, x);
        return ans;
    }
}