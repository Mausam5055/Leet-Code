class Solution {
    public int totalMoney(int n) {
        int weeks = n / 7;
        int days = n % 7;

        int total = 0;

        // full weeks
        for (int i = 0; i < weeks; i++) {
            total += 7 * (i + 1) + 21;
        }

        // remaining days
        for (int i = 0; i < days; i++) {
            total += weeks + 1 + i;
        }

        return total;
    }
}