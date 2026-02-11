class Solution {
    public int canBeTypedWords(String text, String brokenLetters) {
        boolean[] broken = new boolean[26];

        // Mark broken letters
        for (char c : brokenLetters.toCharArray()) {
            broken[c - 'a'] = true;
        }

        int count = 0;

        // Split words by space
        String[] words = text.split(" ");

        for (String word : words) {
            boolean canType = true;

            for (char c : word.toCharArray()) {
                if (broken[c - 'a']) {
                    canType = false;
                    break;
                }
            }

            if (canType) count++;
        }

        return count;
    }
}
