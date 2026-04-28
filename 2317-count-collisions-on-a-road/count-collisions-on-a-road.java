class Solution {
    public int countCollisions(String directions) {
        int n = directions.length();
        int left = 0, right = n - 1;

        // skip leading L
        while (left < n && directions.charAt(left) == 'L') left++;

        // skip trailing R
        while (right >= 0 && directions.charAt(right) == 'R') right--;

        int collisions = 0;

        for (int i = left; i <= right; i++) {
            if (directions.charAt(i) != 'S') {
                collisions++;
            }
        }

        return collisions;
    }
}