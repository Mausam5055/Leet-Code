class Solution {
public:
    long long sumAndMultiply(int n) {
        if (n == 0) return 0;

        vector<int> digits;
        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }

        reverse(digits.begin(), digits.end());

        long long x = 0;
        long long sum = 0;

        for (int d : digits) {
            if (d != 0) {
                x = x * 10 + d;
                sum += d;
            }
        }

        return x * sum;
    }
};