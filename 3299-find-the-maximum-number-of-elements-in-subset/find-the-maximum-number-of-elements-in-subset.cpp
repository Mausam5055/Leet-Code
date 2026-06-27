class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> mp;

        for (int x : nums)
            mp[x]++;

        int ans = 1;

        if (mp.count(1))
            ans = max(ans, mp[1] % 2 ? mp[1] : mp[1] - 1);

        for (auto &[x, f] : mp) {
            if (x == 1) continue;

            long long cur = x;
            int len = 0;

            while (mp.count(cur) && mp[cur] > 1) {
                len += 2;

                if (cur > 1000000000LL) break;
                cur *= cur;
            }

            if (mp.count(cur))
                len++;
            else
                len--;

            ans = max(ans, len);
        }

        return ans;
    }
};