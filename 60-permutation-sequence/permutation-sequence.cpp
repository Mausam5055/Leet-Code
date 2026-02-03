class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> numbers;
        vector<int> fact(n);
        
        // factorials
        fact[0] = 1;
        for (int i = 1; i < n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        
        // numbers list
        for (int i = 1; i <= n; i++) {
            numbers.push_back(i);
        }
        
        // make k zero-based
        k--;
        
        string result = "";
        
        for (int i = n; i >= 1; i--) {
            int idx = k / fact[i - 1];
            result += to_string(numbers[idx]);
            
            numbers.erase(numbers.begin() + idx);
            k %= fact[i - 1];
        }
        
        return result;
    }
};
