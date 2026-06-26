class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions,
                                      vector<int>& healths,
                                      string directions) {

        int n = positions.size();

        vector<array<int,4>> robots;

        for(int i = 0; i < n; i++) {
            robots.push_back({positions[i], healths[i], directions[i], i});
        }

        sort(robots.begin(), robots.end());

        stack<int> st; // indices in robots array

        for(int i = 0; i < n; i++) {

            if(robots[i][2] == 'R') {
                st.push(i);
                continue;
            }

            while(!st.empty() && robots[i][1] > 0) {

                int j = st.top();

                if(robots[j][1] < robots[i][1]) {
                    robots[i][1]--;
                    robots[j][1] = 0;
                    st.pop();
                }
                else if(robots[j][1] > robots[i][1]) {
                    robots[j][1]--;
                    robots[i][1] = 0;
                }
                else {
                    robots[j][1] = 0;
                    robots[i][1] = 0;
                    st.pop();
                }
            }
        }

        vector<pair<int,int>> survivors;

        for(auto &r : robots) {
            if(r[1] > 0) {
                survivors.push_back({r[3], r[1]});
            }
        }

        sort(survivors.begin(), survivors.end());

        vector<int> ans;

        for(auto &[idx, hp] : survivors) {
            ans.push_back(hp);
        }

        return ans;
    }
};