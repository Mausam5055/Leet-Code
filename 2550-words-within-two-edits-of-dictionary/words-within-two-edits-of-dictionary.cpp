#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    vector<string> twoEditWords(vector<string>& queries, vector<string>& dictionary) {
        vector<string> result;
        
        for (const string& q : queries) {
            for (const string& d : dictionary) {
                int diff_count = 0;
                
                for (int i = 0; i < q.length(); ++i) {
                    if (q[i] != d[i]) {
                        diff_count++;
                    }
                    if (diff_count > 2) {
                        break;
                    }
                }
                
                if (diff_count <= 2) {
                    result.push_back(q);
                    break; 
                }
            }
        }
        
        return result;
    }
};