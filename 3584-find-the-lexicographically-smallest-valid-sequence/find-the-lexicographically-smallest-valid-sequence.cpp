#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();

        // last_pos[j] stores the largest index in word1 from which 
        // we can form the suffix word2[j...n-1]
        vector<int> last_pos(n, -1);
        int ptr = m - 1;
        for (int j = n - 1; j >= 0; --j) {
            while (ptr >= 0 && word1[ptr] != word2[j]) {
                ptr--;
            }
            last_pos[j] = ptr;
            if (ptr >= 0) {
                ptr--; // move to next position to match previous char
            }
        }

        vector<int> seq;
        bool used_mismatch = false;
        ptr = 0; // Pointer in word1

        for (int j = 0; j < n; ++j) {
            while (ptr < m) {
                if (word1[ptr] == word2[j]) {
                    seq.push_back(ptr);
                    ptr++;
                    break;
                } else if (!used_mismatch) {
                    // Check if we can afford a mismatch here
                    bool can_finish = (j + 1 == n) || (last_pos[j + 1] > ptr);
                    if (can_finish) {
                        used_mismatch = true;
                        seq.push_back(ptr);
                        ptr++;
                        break;
                    }
                }
                ptr++;
            }
            if (seq.size() != j + 1) {
                return {}; // Sequence couldn't be formed
            }
        }

        return seq;
    }
};