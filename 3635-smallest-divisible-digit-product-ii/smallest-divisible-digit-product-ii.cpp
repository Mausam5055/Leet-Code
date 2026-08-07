#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    string smallestNumber(string num, long long t) {
        // Step 1: Extract Prime Factors from t
        long long temp = t;
        int req2 = 0, req3 = 0, req5 = 0, req7 = 0;
        while (temp % 2 == 0) { req2++; temp /= 2; }
        while (temp % 3 == 0) { req3++; temp /= 3; }
        while (temp % 5 == 0) { req5++; temp /= 5; }
        while (temp % 7 == 0) { req7++; temp /= 7; }
        
        // If t has prime factors other than 2, 3, 5, or 7, it's impossible.
        if (temp > 1) return "-1";

        // Step 2: Precompute minimum digits needed for 2s and 3s
        int dp[60][40];
        for (int i = 0; i < 60; i++) 
            for (int j = 0; j < 40; j++) 
                dp[i][j] = 1e9;
        dp[0][0] = 0;
        
        int c2[] = {0, 0, 1, 0, 2, 0, 1, 0, 3, 0};
        int c3[] = {0, 0, 0, 1, 0, 0, 1, 0, 0, 2};
        
        // Forward DP
        for (int i = 0; i <= 50; i++) {
            for (int j = 0; j <= 30; j++) {
                if (dp[i][j] == 1e9) continue;
                for (int d = 2; d <= 9; d++) {
                    if (d == 5 || d == 7) continue;
                    int ni = min(50, i + c2[d]);
                    int nj = min(30, j + c3[d]);
                    dp[ni][nj] = min(dp[ni][nj], dp[i][j] + 1);
                }
            }
        }
        
        // Suffix minimums so dp[i][j] represents "at least i twos and j threes"
        for (int i = 50; i >= 0; i--) {
            for (int j = 30; j >= 0; j--) {
                if (i < 50) dp[i][j] = min(dp[i][j], dp[i+1][j]);
                if (j < 30) dp[i][j] = min(dp[i][j], dp[i][j+1]);
            }
        }
        
        // Step 3: Check prefix capabilities of `num`
        int n = num.size();
        vector<int> rem2(n + 1, req2), rem3(n + 1, req3);
        vector<int> rem5(n + 1, req5), rem7(n + 1, req7);
        
        int z = 0; // Tracks first occurrence of '0'
        for (int i = 0; i < n; i++) {
            if (num[i] == '0') { z = i; break; }
            z = i + 1;
            int d = num[i] - '0';
            rem2[i+1] = max(0, rem2[i] - c2[d]);
            rem3[i+1] = max(0, rem3[i] - c3[d]);
            rem5[i+1] = max(0, rem5[i] - (d == 5 ? 1 : 0));
            rem7[i+1] = max(0, rem7[i] - (d == 7 ? 1 : 0));
        }
        
        // If the original string itself is valid and has no '0's
        if (z == n && rem2[n] == 0 && rem3[n] == 0 && rem5[n] == 0 && rem7[n] == 0) {
            return num;
        }
        
        // Step 4: Try to branch off from a valid prefix (same length string)
        int start_i = min(n - 1, z);
        string ans = "";
        bool found = false;
        
        for (int i = start_i; i >= 0; i--) {
            int cr2 = rem2[i], cr3 = rem3[i], cr5 = rem5[i], cr7 = rem7[i];
            int start_d = (num[i] - '0') + 1; // Strictly greater than current digit
            
            for (int d = start_d; d <= 9; d++) {
                int nr2 = max(0, cr2 - c2[d]);
                int nr3 = max(0, cr3 - c3[d]);
                int nr5 = max(0, cr5 - (d == 5 ? 1 : 0));
                int nr7 = max(0, cr7 - (d == 7 ? 1 : 0));
                
                int rem_len = n - 1 - i;
                if (nr5 + nr7 + dp[nr2][nr3] <= rem_len) {
                    // It's possible! Construct the rest of the string
                    ans = num.substr(0, i) + to_string(d);
                    for (int k = i + 1; k < n; k++) {
                        for (int nd = 1; nd <= 9; nd++) {
                            int nnr2 = max(0, nr2 - c2[nd]);
                            int nnr3 = max(0, nr3 - c3[nd]);
                            int nnr5 = max(0, nr5 - (nd == 5 ? 1 : 0));
                            int nnr7 = max(0, nr7 - (nd == 7 ? 1 : 0));
                            if (nnr5 + nnr7 + dp[nnr2][nnr3] <= n - 1 - k) {
                                ans += to_string(nd);
                                nr2 = nnr2; nr3 = nnr3; nr5 = nnr5; nr7 = nnr7;
                                break;
                            }
                        }
                    }
                    found = true;
                    break;
                }
            }
            if (found) break;
        }
        
        // Step 5: If no valid replacement of the same length, build a larger one
        if (!found) {
            int L = n + 1;
            while (req5 + req7 + dp[req2][req3] > L) L++;
            
            int nr2 = req2, nr3 = req3, nr5 = req5, nr7 = req7;
            for (int k = 0; k < L; k++) {
                for (int nd = 1; nd <= 9; nd++) {
                    int nnr2 = max(0, nr2 - c2[nd]);
                    int nnr3 = max(0, nr3 - c3[nd]);
                    int nnr5 = max(0, nr5 - (nd == 5 ? 1 : 0));
                    int nnr7 = max(0, nr7 - (nd == 7 ? 1 : 0));
                    if (nnr5 + nnr7 + dp[nnr2][nnr3] <= L - 1 - k) {
                        ans += to_string(nd);
                        nr2 = nnr2; nr3 = nnr3; nr5 = nnr5; nr7 = nnr7;
                        break;
                    }
                }
            }
        }
        
        return ans;
    }
};