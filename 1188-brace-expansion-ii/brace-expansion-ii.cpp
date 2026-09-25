#include <vector>
#include <string>
#include <set>

using namespace std;

class Solution {
public:
    vector<string> braceExpansionII(string expression) {
        int i = 0;
        // Parse the full expression starting from index 0
        set<string> result = expr(expression, i);
        // A std::set automatically keeps the elements sorted and unique
        return vector<string>(result.begin(), result.end());
    }

private:
    // Handles union of terms separated by ','
    set<string> expr(const string& s, int& i) {
        set<string> res;
        set<string> cur = term(s, i);
        for (const string& x : cur) res.insert(x);
        
        while (i < s.size() && s[i] == ',') {
            i++; // Skip ','
            cur = term(s, i);
            for (const string& x : cur) res.insert(x);
        }
        return res;
    }

    // Handles Cartesian product (concatenation) of adjacent factors
    set<string> term(const string& s, int& i) {
        set<string> res = {""}; // Start with an empty string for valid concatenation
        
        // Continue while we haven't hit a union separator or the end of a group
        while (i < s.size() && s[i] != ',' && s[i] != '}') {
            set<string> f = factor(s, i);
            set<string> next_res;
            
            // Cartesian product of the current accumulated result and the new factor
            for (const string& a : res) {
                for (const string& b : f) {
                    next_res.insert(a + b);
                }
            }
            res = move(next_res);
        }
        return res;
    }

    // Handles single characters or grouped expressions wrapped in '{}'
    set<string> factor(const string& s, int& i) {
        if (s[i] == '{') {
            i++; // Skip '{'
            set<string> res = expr(s, i);
            i++; // Skip '}'
            return res;
        } else {
            // It's a lowercase letter
            string str = "";
            str += s[i];
            i++;
            return {str};
        }
    }
};