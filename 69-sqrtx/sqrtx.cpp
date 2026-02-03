class Solution {
public:
    int mySqrt(int x) {
        if (x < 2) return x;   // handles 0 and 1

        int left = 1, right = x / 2;
        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long square = 1LL * mid * mid;

            if (square == x) {
                return mid;
            } 
            else if (square < x) {
                ans = mid;        // store best candidate
                left = mid + 1;
            } 
            else {
                right = mid - 1;
            }
        }
        return ans;
    }
};
