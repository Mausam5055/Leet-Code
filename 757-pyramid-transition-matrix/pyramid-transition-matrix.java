class Solution {
    public boolean pyramidTransition(String bottom, List<String> allowed) {
        // Step 1: build map
        Map<String, List<Character>> map = new HashMap<>();

        for (String s : allowed) {
            String key = s.substring(0, 2);
            char value = s.charAt(2);

            map.computeIfAbsent(key, k -> new ArrayList<>()).add(value);
        }

        return dfs(bottom, map);
    }

    private boolean dfs(String current, Map<String, List<Character>> map) {
        // Base case
        if (current.length() == 1) return true;

        List<String> nextRows = new ArrayList<>();
        buildNextRows(current, 0, new StringBuilder(), map, nextRows);

        for (String next : nextRows) {
            if (dfs(next, map)) return true;
        }

        return false;
    }

    private void buildNextRows(String current, int index, StringBuilder sb,
                               Map<String, List<Character>> map,
                               List<String> nextRows) {

        // If we built full next row
        if (index == current.length() - 1) {
            nextRows.add(sb.toString());
            return;
        }

        String key = current.substring(index, index + 2);

        if (!map.containsKey(key)) return;

        for (char c : map.get(key)) {
            sb.append(c);
            buildNextRows(current, index + 1, sb, map, nextRows);
            sb.deleteCharAt(sb.length() - 1); // backtrack
        }
    }
}