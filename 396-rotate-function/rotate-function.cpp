class Solution {
public:
    int maxRotateFunction(vector<int>& nums) {
        long long sum = 0;
        long long f = 0;
        int n = nums.size();

        for (int i = 0; i < n; i++) {
            sum += nums[i];
            f += 1LL * i * nums[i];
        }

        long long ans = f;

        for (int i = 1; i < n; i++) {
            f = f + sum - 1LL * n * nums[n - i];
            ans = max(ans, f);
        }

        return (int)ans;
    }
};