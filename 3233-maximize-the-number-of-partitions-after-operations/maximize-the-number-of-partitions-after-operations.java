import java.util.*;

class Solution {

    String s;
    int k, n;
    Map<String, Integer> memo = new HashMap<>();

    public int maxPartitionsAfterOperations(String s, int k) {
        this.s = s;
        this.k = k;
        this.n = s.length();

        return dfs(0, 0, 0);
    }

    int dfs(int i, int mask, int changed) {

        if (i == n)
            return 1;

        String key = i + "," + mask + "," + changed;

        if (memo.containsKey(key))
            return memo.get(key);

        int ans = 0;

        int bit = 1 << (s.charAt(i) - 'a');
        int newMask = mask | bit;

        if (Integer.bitCount(newMask) > k)
            ans = Math.max(ans, 1 + dfs(i + 1, bit, changed));
        else
            ans = Math.max(ans, dfs(i + 1, newMask, changed));

        if (changed == 0) {

            for (int c = 0; c < 26; c++) {

                bit = 1 << c;
                newMask = mask | bit;

                if (Integer.bitCount(newMask) > k)
                    ans = Math.max(ans, 1 + dfs(i + 1, bit, 1));
                else
                    ans = Math.max(ans, dfs(i + 1, newMask, 1));
            }
        }

        memo.put(key, ans);
        return ans;
    }
}