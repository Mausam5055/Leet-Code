class Solution {
  int numDecodings(String s) {
    // If string starts with '0', it is invalid
    if (s.isEmpty || s[0] == '0') return 0;

    int n = s.length;

    // dp[i] = number of ways to decode s[0..i-1]
    List<int> dp = List.filled(n + 1, 0);

    // Base cases
    dp[0] = 1; // Empty string
    dp[1] = 1; // Already checked s[0] != '0'

    for (int i = 2; i <= n; i++) {

      // ----- Single digit check -----
      int oneDigit = int.parse(s.substring(i - 1, i));
      if (oneDigit >= 1) {
        dp[i] += dp[i - 1];
      }

      // ----- Two digit check -----
      int twoDigit = int.parse(s.substring(i - 2, i));
      if (twoDigit >= 10 && twoDigit <= 26) {
        dp[i] += dp[i - 2];
      }
    }

    return dp[n];
  }
}
