class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int n = words.size();
        int i = 0;

        while (i < n) {
            int lineLen = words[i].length();
            int j = i + 1;

            // Greedily pack words
            while (j < n && lineLen + 1 + words[j].length() <= maxWidth) {
                lineLen += 1 + words[j].length();
                j++;
            }

            int wordsCount = j - i;
            string line;

            // Case 1: Last line OR single word
            if (j == n || wordsCount == 1) {
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) line += " ";
                }
                // Pad remaining spaces at end
                line += string(maxWidth - line.length(), ' ');
            }
            // Case 2: Fully justified
            else {
                int totalWordLen = 0;
                for (int k = i; k < j; k++)
                    totalWordLen += words[k].length();

                int totalSpaces = maxWidth - totalWordLen;
                int gaps = wordsCount - 1;
                int spaceEach = totalSpaces / gaps;
                int extraSpaces = totalSpaces % gaps;

                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k < j - 1) {
                        line += string(spaceEach + (extraSpaces-- > 0 ? 1 : 0), ' ');
                    }
                }
            }

            result.push_back(line);
            i = j;
        }

        return result;
    }
};
