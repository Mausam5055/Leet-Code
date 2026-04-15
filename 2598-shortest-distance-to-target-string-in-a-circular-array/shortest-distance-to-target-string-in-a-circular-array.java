class Solution {
    public int closestTarget(String[] words, String target, int startIndex) {
        int n = words.length;
        int minDist = Integer.MAX_VALUE;

        for (int i = 0; i < n; i++) {
            if (words[i].equals(target)) {
                int diff = Math.abs(i - startIndex);
                int distance = Math.min(diff, n - diff);
                minDist = Math.min(minDist, distance);
            }
        }

        return minDist == Integer.MAX_VALUE ? -1 : minDist;
    }
}