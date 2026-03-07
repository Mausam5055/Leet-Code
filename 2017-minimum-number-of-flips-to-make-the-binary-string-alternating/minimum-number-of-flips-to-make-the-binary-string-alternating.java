class Solution {
    public int minFlips(String s) {
        int n = s.length();
        String s2 = s + s;

        int diff1 = 0;
        int diff2 = 0;
        int res = Integer.MAX_VALUE;

        for(int i = 0; i < s2.length(); i++) {

            char c = s2.charAt(i);

            char alt1 = (i % 2 == 0) ? '0' : '1';
            char alt2 = (i % 2 == 0) ? '1' : '0';

            if(c != alt1) diff1++;
            if(c != alt2) diff2++;

            if(i >= n) {
                char prev = s2.charAt(i-n);

                char alt1Prev = ((i-n) % 2 == 0) ? '0' : '1';
                char alt2Prev = ((i-n) % 2 == 0) ? '1' : '0';

                if(prev != alt1Prev) diff1--;
                if(prev != alt2Prev) diff2--;
            }

            if(i >= n-1) {
                res = Math.min(res, Math.min(diff1, diff2));
            }
        }

        return res;
    }
}