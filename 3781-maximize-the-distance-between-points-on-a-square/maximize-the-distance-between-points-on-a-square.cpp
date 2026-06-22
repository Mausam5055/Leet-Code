class Solution {
public:
    using ll = long long;

    int maxDistance(int side, vector<vector<int>>& points, int k) {
        int n = points.size();
        ll L = 4LL * side;

        vector<ll> pos;

        for (auto &p : points) {
            ll x = p[0], y = p[1];

            if (y == 0) pos.push_back(x);
            else if (x == side) pos.push_back(side + y);
            else if (y == side) pos.push_back(3LL * side - x);
            else pos.push_back(4LL * side - y);
        }

        sort(pos.begin(), pos.end());

        auto check = [&](ll d) -> bool {
            vector<ll> ext = pos;
            for (ll x : pos) ext.push_back(x + L);

            int m = ext.size();

            vector<int> nxt(m);

            int j = 0;
            for (int i = 0; i < m; i++) {
                if (j < i + 1) j = i + 1;

                while (j < m && ext[j] - ext[i] < d) j++;

                nxt[i] = j;
            }

            const int LOG = 6; // k <= 25

            vector<vector<int>> up(LOG, vector<int>(m, m));

            for (int i = 0; i < m; i++)
                up[0][i] = min(nxt[i], m);

            for (int b = 1; b < LOG; b++) {
                for (int i = 0; i < m; i++) {
                    int mid = up[b - 1][i];
                    up[b][i] = (mid < m ? up[b - 1][mid] : m);
                }
            }

            for (int start = 0; start < n; start++) {
                int cur = start;
                int need = k - 1;

                for (int b = 0; b < LOG; b++) {
                    if (need & (1 << b)) {
                        cur = up[b][cur];
                        if (cur >= start + n) break;
                    }
                }

                if (cur >= start + n) continue;

                ll gap = ext[start + n] - ext[cur];

                if (gap >= d) return true;
            }

            return false;
        };

        ll lo = 0, hi = 2LL * side;

        while (lo < hi) {
            ll mid = (lo + hi + 1) >> 1;

            if (check(mid))
                lo = mid;
            else
                hi = mid - 1;
        }

        return (int)lo;
    }
};