class Solution {
public:
    string decodeCiphertext(string encodedText, int rows) {
        if (rows == 1) return encodedText;

        int n = encodedText.size();
        int cols = n / rows;

        string ans;

        for (int startCol = 0; startCol < cols; startCol++) {
            int r = 0, c = startCol;

            while (r < rows && c < cols) {
                ans += encodedText[r * cols + c];
                r++;
                c++;
            }
        }

        while (!ans.empty() && ans.back() == ' ')
            ans.pop_back();

        return ans;
    }
};