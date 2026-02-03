import java.util.HashMap;

class Solution {
    public int maxPoints(int[][] points) {
        int n = points.length;
        if (n <= 2) return n;

        int result = 0;

        for (int i = 0; i < n; i++) {
            HashMap<String, Integer> map = new HashMap<>();
            int max = 0;

            for (int j = i + 1; j < n; j++) {
                int dx = points[j][0] - points[i][0];
                int dy = points[j][1] - points[i][1];

                if (dx == 0) { // vertical line
                    dy = 1;
                } else if (dy == 0) { // horizontal line
                    dx = 1;
                } else {
                    // normalize sign
                    if (dx < 0) {
                        dx = -dx;
                        dy = -dy;
                    }
                    int gcd = gcd(Math.abs(dx), Math.abs(dy));
                    dx /= gcd;
                    dy /= gcd;
                }

                String slope = dy + "/" + dx;
                int count = map.getOrDefault(slope, 0) + 1;
                map.put(slope, count);
                max = Math.max(max, count);
            }

            result = Math.max(result, max + 1); // +1 for anchor point
        }

        return result;
    }

    private int gcd(int a, int b) {
        return b == 0 ? a : gcd(b, a % b);
    }
}
