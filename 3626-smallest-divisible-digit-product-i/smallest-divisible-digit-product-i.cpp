class Solution {
public:
    int smallestNumber(int n, int t) {
        int curr = n;
        while (true) {
            int product = 1;
            int temp = curr;
            while (temp > 0) {
                product *= temp % 10;
                temp /= 10;
            }
            if (product % t == 0) {
                return curr;
            }
            curr++;
        }
    }
};