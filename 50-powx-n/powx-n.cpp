class Solution {
public:
    double myPow(double x, int n) {
        long long exp = n;     // prevent overflow
        double result = 1.0;

        // handle negative exponent
        if (exp < 0) {
            x = 1 / x;
            exp = -exp;
        }

        // binary exponentiation
        while (exp > 0) {
            if (exp % 2 == 1) {
                result *= x;
            }
            x *= x;
            exp /= 2;
        }

        return result;
    }
};
