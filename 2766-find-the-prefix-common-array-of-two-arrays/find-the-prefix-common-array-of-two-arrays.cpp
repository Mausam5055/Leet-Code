class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();

        vector<int> seenA(n + 1, 0);
        vector<int> seenB(n + 1, 0);
        vector<int> ans(n);

        int common = 0;

        for (int i = 0; i < n; i++) {
            seenA[A[i]] = 1;
            seenB[B[i]] = 1;

            if (seenB[A[i]]) common++;
            if (seenA[B[i]]) common++;

            if (A[i] == B[i]) common--;

            ans[i] = common;
        }

        return ans;
    }
};