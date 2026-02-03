class Solution {
  bool isInterleave(String s1, String s2, String s3) {
    int n = s1.length;
    int m = s2.length;

    // Length mismatch → impossible
    if (n + m != s3.length) return false;

    // dp[j] = whether s3[0..i+j-1] can be formed using
    // i chars from s1 and j chars from s2
    List<bool> dp = List.filled(m + 1, false);

    dp[0] = true;

    // Initialize first row (using only s2)
    for (int j = 1; j <= m; j++) {
      dp[j] = dp[j - 1] && s2[j - 1] == s3[j - 1];
    }

    // Fill DP row by row
    for (int i = 1; i <= n; i++) {
      // First column (using only s1)
      dp[0] = dp[0] && s1[i - 1] == s3[i - 1];

      for (int j = 1; j <= m; j++) {
        dp[j] =
            (dp[j] && s1[i - 1] == s3[i + j - 1]) ||
            (dp[j - 1] && s2[j - 1] == s3[i + j - 1]);
      }
    }

    return dp[m];
  }
}
