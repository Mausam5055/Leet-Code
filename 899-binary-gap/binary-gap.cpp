class Solution {
public:
    int binaryGap(int n) {
        int last = -1, ans = 0, pos = 0;

        while (n) {
            if (n & 1) {
                if (last != -1)
                    ans = max(ans, pos - last);
                last = pos;
            }
            n >>= 1;
            pos++;
        }

        return ans;
    }
};