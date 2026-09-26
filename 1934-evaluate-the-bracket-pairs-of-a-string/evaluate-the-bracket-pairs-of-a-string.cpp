#include <string>
#include <vector>
#include <unordered_map>

class Solution {
public:
    std::string evaluate(std::string s, std::vector<std::vector<std::string>>& knowledge) {
        // Step 1: Populate the hash map for O(1) lookups
        std::unordered_map<std::string, std::string> dict;
        for (const auto& pair : knowledge) {
            dict[pair[0]] = pair[1];
        }
        
        std::string result = "";
        std::string current_key = "";
        bool in_bracket = false;
        
        // Step 2: Parse the string
        for (char c : s) {
            if (c == '(') {
                in_bracket = true;
                current_key = ""; // Reset the key for the new bracket pair
            } else if (c == ')') {
                in_bracket = false;
                // Evaluate the key and append to result
                if (dict.count(current_key)) {
                    result += dict[current_key];
                } else {
                    result += "?";
                }
            } else {
                if (in_bracket) {
                    current_key += c; // Build the key
                } else {
                    result += c;      // Build the regular string
                }
            }
        }
        
        return result;
    }
};