class Solution {
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) {
        long long sum = 0;
        int negatives = 0;
        int minAbs = INT_MAX;

        for (auto &row : matrix) {
            for (int x : row) {
                sum += abs((long long)x);
                minAbs = min(minAbs, abs(x));

                if (x < 0)
                    negatives++;
            }
        }

        if (negatives % 2 == 0)
            return sum;

        return sum - 2LL * minAbs;
    }
};