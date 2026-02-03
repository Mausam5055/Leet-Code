class Solution {
    public List<String> wordBreak(String s, List<String> wordDict) {
        Set<String> wordSet = new HashSet<>(wordDict);
        Map<Integer, List<String>> memo = new HashMap<>();
        return dfs(0, s, wordSet, memo);
    }

    private List<String> dfs(int start, String s, Set<String> wordSet,
                             Map<Integer, List<String>> memo) {

        if (memo.containsKey(start)) {
            return memo.get(start);
        }

        List<String> res = new ArrayList<>();

        // base case: reached end
        if (start == s.length()) {
            res.add("");
            return res;
        }

        for (int end = start + 1; end <= s.length(); end++) {
            String word = s.substring(start, end);

            if (wordSet.contains(word)) {
                List<String> subList = dfs(end, s, wordSet, memo);

                for (String sub : subList) {
                    if (sub.isEmpty()) {
                        res.add(word);
                    } else {
                        res.add(word + " " + sub);
                    }
                }
            }
        }

        memo.put(start, res);
        return res;
    }
}
