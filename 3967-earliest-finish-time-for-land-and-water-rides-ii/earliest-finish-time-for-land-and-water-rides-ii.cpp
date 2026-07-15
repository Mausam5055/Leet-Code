class Solution {
public:
    int solve(vector<int>& Astart, vector<int>& Adur,
              vector<int>& Bstart, vector<int>& Bdur) {

        int m = Bstart.size();

        vector<pair<int,int>> rides;
        for(int i=0;i<m;i++)
            rides.push_back({Bstart[i], Bdur[i]});

        sort(rides.begin(), rides.end());

        vector<int> prefDur(m), sufFinish(m);

        prefDur[0] = rides[0].second;
        for(int i=1;i<m;i++)
            prefDur[i] = min(prefDur[i-1], rides[i].second);

        sufFinish[m-1] = rides[m-1].first + rides[m-1].second;
        for(int i=m-2;i>=0;i--)
            sufFinish[i] = min(sufFinish[i+1],
                               rides[i].first + rides[i].second);

        int ans = INT_MAX;

        for(int i=0;i<Astart.size();i++) {
            int finish = Astart[i] + Adur[i];

            int idx = upper_bound(
                rides.begin(), rides.end(),
                make_pair(finish, INT_MAX)
            ) - rides.begin() - 1;

            if(idx >= 0)
                ans = min(ans, finish + prefDur[idx]);

            if(idx + 1 < m)
                ans = min(ans, sufFinish[idx+1]);
        }

        return ans;
    }

    int earliestFinishTime(vector<int>& landStartTime,
                           vector<int>& landDuration,
                           vector<int>& waterStartTime,
                           vector<int>& waterDuration) {

        return min(
            solve(landStartTime, landDuration,
                  waterStartTime, waterDuration),
            solve(waterStartTime, waterDuration,
                  landStartTime, landDuration)
        );
    }
};