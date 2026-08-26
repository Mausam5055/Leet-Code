class Solution:
    def maximumScore(self, grid: list[list[int]]) -> int:
        n = len(grid)
        
        # pref[c][k] stores the sum of the first k cells in column c
        pref = [[0] * (n + 1) for _ in range(n)]
        for c in range(n):
            for r in range(n):
                pref[c][r + 1] = pref[c][r] + grid[r][c]
                
        def get_val(c, k, q):
            """Returns the sum of white cells in col c from row q to k-1"""
            if k > q:
                return pref[c][k] - pref[c][q]
            return 0

        # dp[q][p] -> max score where current col height is q, prev col height is p
        dp = [[float('-inf')] * (n + 1) for _ in range(n + 1)]
        
        # Base case for column 0 (imaginary col -1 has height 0)
        for q in range(n + 1):
            dp[q][0] = 0
            
        for c in range(n):
            new_dp = [[float('-inf')] * (n + 1) for _ in range(n + 1)]
            
            for q in range(n + 1):
                dp_row = dp[q]
                
                # Precompute prefix maxes for p <= r
                pref_max = [float('-inf')] * (n + 1)
                curr_max = float('-inf')
                for p in range(n + 1):
                    if dp_row[p] > curr_max:
                        curr_max = dp_row[p]
                    pref_max[p] = curr_max
                    
                # Precompute suffix maxes for p > r
                suff_max = [float('-inf')] * (n + 2)
                curr_max = float('-inf')
                for p in range(n, -1, -1):
                    val = dp_row[p] + get_val(c, p, q)
                    if val > curr_max:
                        curr_max = val
                    suff_max[p] = curr_max
                    
                # Calculate transitions to the next column's height (r)
                for r in range(n + 1):
                    # Case 1: p <= r -> score depends on r
                    ans1 = pref_max[r] + get_val(c, r, q)
                    # Case 2: p > r -> score depends on p
                    ans2 = suff_max[r + 1]
                    
                    new_dp[r][q] = max(ans1, ans2)
                    
            dp = new_dp
            
        # The imaginary column n has height 0, so we just look at dp[0][q]
        return max(dp[0])