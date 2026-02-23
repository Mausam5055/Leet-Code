import java.util.*;

class Solution {
    public boolean hasAllCodes(String s, int k) {
        int need = 1 << k;          // total possible binary codes = 2^k
        Set<String> seen = new HashSet<>();

        for (int i = 0; i <= s.length() - k; i++) {
            String sub = s.substring(i, i + k);
            if (!seen.contains(sub)) {
                seen.add(sub);
                need--;
                if (need == 0) return true;  // all codes found early
            }
        }
        
        return false;
    }
}