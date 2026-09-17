#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string mapWordWeights(vector<string>& words, vector<int>& weights) {
        string result = "";
        result.reserve(words.size()); 
        
        for (const string& word : words) {
            int current_weight = 0;
            
            // Calculate the total weight of the current word
            for (char c : word) {
                current_weight += weights[c - 'a'];
            }
            
            // Find modulo 26 and map to the reverse alphabetical character
            int remainder = current_weight % 26;
            result += (char)('z' - remainder);
        }
        
        return result;
    }
};