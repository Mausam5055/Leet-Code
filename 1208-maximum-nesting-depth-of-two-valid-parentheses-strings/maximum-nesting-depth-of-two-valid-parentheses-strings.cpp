#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        vector<int> result;
        result.reserve(seq.length());
        
        int depth = 0;
        for (char c : seq) {
            if (c == '(') {
                // Assign to 0 or 1 based on current depth parity
                result.push_back(depth % 2);
                depth++;
            } else {
                // Decrease depth first to match the corresponding '(' parity
                depth--;
                result.push_back(depth % 2);
            }
        }
        
        return result;
    }
};