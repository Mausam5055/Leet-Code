class Solution {
public:
    vector<string> cellsInRange(string s) {
        vector<string> ans;

        for (char col = s[0]; col <= s[3]; col++) {
            for (char row = s[1]; row <= s[4]; row++) {
                string cell = "";
                cell += col;
                cell += row;
                ans.push_back(cell);
            }
        }

        return ans;
    }
};