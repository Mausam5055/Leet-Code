class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {

        int MAX = 50000;

        // 1. Frequency of each number
        vector<int> freq(MAX + 1);

        for (int x : nums) {
            freq[x]++;
        }

        // exact[g] = number of pairs having GCD exactly g
        vector<long long> exact(MAX + 1, 0);

        // 2. Find exact GCD counts
        for (int g = MAX; g >= 1; g--) {

            long long cnt = 0;

            // Count numbers divisible by g
            for (int multiple = g; multiple <= MAX; multiple += g) {
                cnt += freq[multiple];
            }

            // Number of pairs where both are divisible by g
            exact[g] = cnt * (cnt - 1) / 2;

            // Remove pairs whose GCD is a larger multiple of g
            for (int multiple = 2 * g; multiple <= MAX; multiple += g) {
                exact[g] -= exact[multiple];
            }
        }

        // 3. Prefix sum
        // prefix[g] = number of pairs whose GCD <= g
        vector<long long> prefix(MAX + 1);

        for (int g = 1; g <= MAX; g++) {
            prefix[g] = prefix[g - 1] + exact[g];
        }

        // 4. Answer queries using binary search
        vector<int> answer;

        for (long long q : queries) {

            // We need the smallest g such that
            // prefix[g] > q
            int left = 1;
            int right = MAX;

            while (left < right) {
                int mid = left + (right - left) / 2;

                if (prefix[mid] > q) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            }

            answer.push_back(left);
        }

        return answer;
    }
};