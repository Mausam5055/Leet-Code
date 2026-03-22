class Solution {
    public int nextBeautifulNumber(int n) {
        int num = n + 1;
        
        while (true) {
            if (isBalanced(num)) {
                return num;
            }
            num++;
        }
    }

    private boolean isBalanced(int num) {
        int[] freq = new int[10];
        
        int temp = num;
        while (temp > 0) {
            int digit = temp % 10;
            freq[digit]++;
            temp /= 10;
        }

        for (int d = 0; d <= 9; d++) {
            if (freq[d] > 0 && freq[d] != d) {
                return false;
            }
        }

        return true;
    }
}