class Solution {
  List<String> restoreIpAddresses(String s) {
    List<String> result = [];

    // Helper backtracking function
    void backtrack(int index, int parts, List<String> current) {
      // If 4 parts are formed
      if (parts == 4) {
        // Check if entire string is used
        if (index == s.length) {
          result.add(current.join('.'));
        }
        return;
      }

      // Prune: remaining characters must fit remaining parts
      int remainingChars = s.length - index;
      int remainingParts = 4 - parts;
      if (remainingChars < remainingParts || remainingChars > remainingParts * 3) {
        return;
      }

      // Try segments of length 1 to 3
      for (int len = 1; len <= 3; len++) {
        if (index + len > s.length) break;

        String segment = s.substring(index, index + len);

        // Rule 1: No leading zeros
        if (segment.length > 1 && segment.startsWith('0')) continue;

        int value = int.parse(segment);

        // Rule 2: Value must be <= 255
        if (value > 255) continue;

        current.add(segment);
        backtrack(index + len, parts + 1, current);
        current.removeLast(); // backtrack
      }
    }

    backtrack(0, 0, []);
    return result;
  }
}
