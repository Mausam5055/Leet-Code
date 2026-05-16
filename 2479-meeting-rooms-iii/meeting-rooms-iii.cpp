class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {

        sort(meetings.begin(), meetings.end());

        // free rooms
        priority_queue<int, vector<int>, greater<int>> available;

        // {endTime, roomNo}
        priority_queue<
            pair<long long,int>,
            vector<pair<long long,int>>,
            greater<pair<long long,int>>
        > busy;

        vector<int> count(n, 0);

        // initially all rooms are free
        for (int i = 0; i < n; i++) {
            available.push(i);
        }

        for (auto &m : meetings) {

            long long start = m[0];
            long long end = m[1];
            long long duration = end - start;

            // free rooms whose meetings ended
            while (!busy.empty() && busy.top().first <= start) {

                int room = busy.top().second;
                busy.pop();

                available.push(room);
            }

            // if free room exists
            if (!available.empty()) {

                int room = available.top();
                available.pop();

                busy.push({end, room});
                count[room]++;
            }
            else {

                // delay meeting
                auto [freeTime, room] = busy.top();
                busy.pop();

                busy.push({freeTime + duration, room});
                count[room]++;
            }
        }

        int ans = 0;

        for (int i = 1; i < n; i++) {

            if (count[i] > count[ans]) {
                ans = i;
            }
        }

        return ans;
    }
};