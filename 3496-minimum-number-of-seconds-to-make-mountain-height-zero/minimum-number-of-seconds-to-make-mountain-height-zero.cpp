class Solution {
public:
    bool can(long long T, int mountainHeight, vector<int>& workerTimes) {
        long long removed = 0;

        for (int w : workerTimes) {
            long long k = (2LL * T) / w;

            long long x = (long long)((sqrtl(1.0L + 4.0L * k) - 1.0L) / 2.0L);

            while ((long long)w * x * (x + 1) / 2 > T) x--;
            while ((long long)w * (x + 1) * (x + 2) / 2 <= T) x++;

            removed += x;

            if (removed >= mountainHeight)
                return true;
        }

        return false;
    }

    long long minNumberOfSeconds(int mountainHeight, vector<int>& workerTimes) {
        long long low = 0;

        long long mn = *min_element(workerTimes.begin(), workerTimes.end());

        long long high = mn * 1LL * mountainHeight * (mountainHeight + 1) / 2;

        while (low < high) {
            long long mid = low + (high - low) / 2;

            if (can(mid, mountainHeight, workerTimes))
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};