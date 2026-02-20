class Solution {
    public String makeLargestSpecial(String s) {
        int count = 0;
        int start = 0;
        List<String> list = new ArrayList<>();

        for (int i = 0; i < s.length(); i++) {
            if (s.charAt(i) == '1') count++;
            else count--;

            // Found a primitive special substring
            if (count == 0) {
                // Recursively optimize inside
                String inner = s.substring(start + 1, i);
                list.add("1" + makeLargestSpecial(inner) + "0");
                start = i + 1;
            }
        }

        // Sort descending for largest lexicographic result
        Collections.sort(list, Collections.reverseOrder());

        StringBuilder result = new StringBuilder();
        for (String str : list) result.append(str);

        return result.toString();
    }
}