class Solution {
public:
    using ll = long long;
    const ll INF = 1e18;

    vector<int> robots;
    vector<vector<int>> factories;
    vector<vector<ll>> dp;

    ll solve(int i, int j) {
        if (i == robots.size()) return 0;
        if (j == factories.size()) return INF;

        if (dp[i][j] != -1) return dp[i][j];

        ll ans = solve(i, j + 1);

        ll cost = 0;
        for (int k = 0; k < factories[j][1] && i + k < robots.size(); k++) {
            cost += abs((ll)robots[i + k] - factories[j][0]);
            ans = min(ans, cost + solve(i + k + 1, j + 1));
        }

        return dp[i][j] = ans;
    }

    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        sort(robot.begin(), robot.end());
        sort(factory.begin(), factory.end());

        robots = robot;
        factories = factory;

        dp.assign(robot.size() + 1, vector<ll>(factory.size() + 1, -1));

        return solve(0, 0);
    }
};