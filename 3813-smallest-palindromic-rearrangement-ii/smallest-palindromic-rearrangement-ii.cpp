class Solution {
public:
    static const int CAP = 1000000;

    // Returns C(n, r), capped at CAP + 1.
    int combCap(int n, int r) {
        if (r < 0 || r > n) return 0;
        r = min(r, n - r);

        long long res = 1;
        for (int i = 1; i <= r; i++) {
            res = (res * (n - r + i)) / i;
            if (res > CAP) return CAP + 1;
        }
        return (int)res;
    }

    // Number of distinct permutations of the multiset "cnt", capped at CAP + 1.
    int countWays(vector<int> &cnt) {
        int rem = 0;
        for (int x : cnt) rem += x;

        long long ans = 1;
        int left = rem;

        for (int c : cnt) {
            if (c == 0) continue;
            ans *= combCap(left, c);
            if (ans > CAP) return CAP + 1;
            left -= c;
        }
        return (int)ans;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);
        for (char c : s) freq[c - 'a']++;

        vector<int> half(26, 0);
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2) mid = char('a' + i);
        }

        if (countWays(half) < k) return "";

        int halfLen = s.size() / 2;
        string left = "";

        for (int pos = 0; pos < halfLen; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                int ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                } else {
                    k -= ways;
                    half[c]++;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        if (s.size() % 2)
            return left + string(1, mid) + right;
        return left + right;
    }
};