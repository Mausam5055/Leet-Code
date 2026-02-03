class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        m, n = len(s), len(p)
        
        # dp[i][j] = True if s[:i] matches p[:j]
        dp = [[False] * (n + 1) for _ in range(m + 1)]
        dp[0][0] = True
        
        # Handle patterns like a*, a*b*, a*b*c* at the beginning
        for j in range(2, n + 1):
            if p[j - 1] == '*':
                dp[0][j] = dp[0][j - 2]
        
        # Fill DP table
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                
                # Case 1: direct match or '.'
                if p[j - 1] == s[i - 1] or p[j - 1] == '.':
                    dp[i][j] = dp[i - 1][j - 1]
                
                # Case 2: '*'
                elif p[j - 1] == '*':
                    # Option A: Treat '*' as zero occurrences (remove previous char + '*')
                    dp[i][j] = dp[i][j - 2]
                    
                    # Option B: If previous char matches, use '*' to match more characters
                    if p[j - 2] == s[i - 1] or p[j - 2] == '.':
                        dp[i][j] |= dp[i - 1][j]
        
        return dp[m][n]
