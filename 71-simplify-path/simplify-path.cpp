class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stack;
        string curr;
        
        for (int i = 0; i <= path.size(); i++) {
            if (i == path.size() || path[i] == '/') {
                if (curr == "" || curr == ".") {
                    // do nothing
                } 
                else if (curr == "..") {
                    if (!stack.empty())
                        stack.pop_back();
                } 
                else {
                    stack.push_back(curr);
                }
                curr.clear();
            } 
            else {
                curr += path[i];
            }
        }

        if (stack.empty()) return "/";

        string result;
        for (string &dir : stack) {
            result += "/" + dir;
        }
        return result;
    }
};
