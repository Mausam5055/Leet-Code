class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        unordered_set<int> prefixes;

        // Store all prefixes of arr1
        for (int num : arr1) {
            while (num > 0) {
                prefixes.insert(num);
                num /= 10;
            }
        }

        int ans = 0;

        // Check prefixes of arr2
        for (int num : arr2) {
            while (num > 0) {
                if (prefixes.count(num)) {
                    ans = max(ans, (int)to_string(num).size());
                    break; // longest prefix for this number found
                }
                num /= 10;
            }
        }

        return ans;
    }
};