class Solution {
  final Map<String, bool> memo = {};

  bool isScramble(String s1, String s2) {
    // Memo key
    String key = "$s1|$s2";
    if (memo.containsKey(key)) return memo[key]!;

    // Base cases
    if (s1 == s2) return memo[key] = true;
    if (!_sameChars(s1, s2)) return memo[key] = false;

    int n = s1.length;

    for (int i = 1; i < n; i++) {
      // Case 1: no swap
      if (isScramble(s1.substring(0, i), s2.substring(0, i)) &&
          isScramble(s1.substring(i), s2.substring(i))) {
        return memo[key] = true;
      }

      // Case 2: swap
      if (isScramble(s1.substring(0, i), s2.substring(n - i)) &&
          isScramble(s1.substring(i), s2.substring(0, n - i))) {
        return memo[key] = true;
      }
    }

    return memo[key] = false;
  }

  bool _sameChars(String a, String b) {
    if (a.length != b.length) return false;

    List<int> count = List.filled(26, 0);
    for (int i = 0; i < a.length; i++) {
      count[a.codeUnitAt(i) - 97]++;
      count[b.codeUnitAt(i) - 97]--;
    }
    for (int c in count) {
      if (c != 0) return false;
    }
    return true;
  }
}
