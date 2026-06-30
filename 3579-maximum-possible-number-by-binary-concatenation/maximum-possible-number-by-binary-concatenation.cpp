class Solution {
public:
    int maxGoodNumber(vector<int>& nums) {
        vector<string> bin(3);

        for (int i = 0; i < 3; i++) {
            bin[i] = bitset<7>(nums[i]).to_string();

            // Remove leading zeros
            int pos = bin[i].find('1');
            bin[i] = bin[i].substr(pos);
        }

        vector<int> p = {0, 1, 2};
        int ans = 0;

        do {
            string s = bin[p[0]] + bin[p[1]] + bin[p[2]];
            ans = max(ans, stoi(s, nullptr, 2));
        } while (next_permutation(p.begin(), p.end()));

        return ans;
    }
};