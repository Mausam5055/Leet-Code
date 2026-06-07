class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.size();
        int m = str2.size();

        string ans(n + m - 1, '?');
        vector<bool> fixed(n + m - 1, false);

        // Apply T constraints
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    if (ans[i + j] != '?' &&
                        ans[i + j] != str2[j])
                        return "";

                    ans[i + j] = str2[j];
                    fixed[i + j] = true;
                }
            }
        }

        // Fill remaining with 'a'
        for (char &c : ans) {
            if (c == '?') c = 'a';
        }

        // Handle F constraints
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F') {

                bool equal = true;

                for (int j = 0; j < m; j++) {
                    if (ans[i + j] != str2[j]) {
                        equal = false;
                        break;
                    }
                }

                if (!equal) continue;

                bool changed = false;

                for (int j = m - 1; j >= 0; j--) {
                    int pos = i + j;

                    if (!fixed[pos]) {
                        ans[pos] =
                            (ans[pos] == 'a' ? 'b' : 'a');

                        changed = true;
                        break;
                    }
                }

                if (!changed) return "";
            }
        }

        return ans;
    }
};