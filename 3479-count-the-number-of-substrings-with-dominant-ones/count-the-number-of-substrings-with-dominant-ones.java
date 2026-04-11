import java.util.*;

class Solution {
    public int numberOfSubstrings(String s) {
        int n = s.length();
        List<Integer> zeroPos = new ArrayList<>();

        // store zero positions
        for (int i = 0; i < n; i++) {
            if (s.charAt(i) == '0') {
                zeroPos.add(i);
            }
        }

        int ans = 0;

        // Case 1: substrings with NO zeros
        int count = 0;
        for (char c : s.toCharArray()) {
            if (c == '1') {
                count++;
                ans += count;
            } else {
                count = 0;
            }
        }

        // Case 2: substrings with z >= 1 zeros
        int m = zeroPos.size();

        for (int z = 1; z * z <= n; z++) {
            for (int i = 0; i + z - 1 < m; i++) {

                int leftZero = zeroPos.get(i);
                int rightZero = zeroPos.get(i + z - 1);

                int leftBound = (i == 0) ? 0 : zeroPos.get(i - 1) + 1;
                int rightBound = (i + z == m) ? n - 1 : zeroPos.get(i + z) - 1;

                int totalLen = rightZero - leftZero + 1;
                int ones = totalLen - z;

                // we need ones >= z*z
                int extra = Math.max(0, z * z - ones);

                int leftChoices = leftZero - leftBound + 1;
                int rightChoices = rightBound - rightZero + 1;

                // count valid expansions
                int valid = 0;

                for (int l = 0; l < leftChoices; l++) {
                    int needRight = extra - l;
                    if (needRight < 0) needRight = 0;
                    if (needRight < rightChoices) {
                        valid += (rightChoices - needRight);
                    }
                }

                ans += valid;
            }
        }

        return ans;
    }
}