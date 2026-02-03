class Solution {
  int numTrees(int n) {
    // dp[i] = number of unique BSTs with i nodes
    List<int> dp = List.filled(n + 1, 0);

    dp[0] = 1; // empty tree
    dp[1] = 1; // single node

    // Compute dp values from 2 to n
    for (int nodes = 2; nodes <= n; nodes++) {
      for (int root = 1; root <= nodes; root++) {
        dp[nodes] += dp[root - 1] * dp[nodes - root];
      }
    }

    return dp[n];
  }
}
