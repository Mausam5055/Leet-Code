class Solution {
public:
    int maximizeSquareArea(int m, int n,
                           vector<int>& hFences,
                           vector<int>& vFences) {

        const long long MOD = 1e9 + 7;

        hFences.push_back(1);
        hFences.push_back(m);

        vFences.push_back(1);
        vFences.push_back(n);

        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());

        unordered_set<long long> hDist;

        int H = hFences.size();
        int V = vFences.size();

        for (int i = 0; i < H; i++) {
            for (int j = i + 1; j < H; j++) {
                hDist.insert((long long)hFences[j] - hFences[i]);
            }
        }

        long long best = -1;

        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {

                long long d = (long long)vFences[j] - vFences[i];

                if (hDist.count(d))
                    best = max(best, d);
            }
        }

        if (best == -1) return -1;

        return (best * best) % MOD;
    }
};