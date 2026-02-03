class Solution {
    public int strStr(String haystack, String needle) {
        int n = haystack.length();
        int m = needle.length();

        // If needle is longer than haystack, impossible
        if (m > n) return -1;

        // Try every possible starting index
        for (int i = 0; i <= n - m; i++) {
            int j = 0;
            while (j < m && haystack.charAt(i + j) == needle.charAt(j)) {
                j++;
            }
            if (j == m) return i; // full match found
        }

        return -1;
    }
}
