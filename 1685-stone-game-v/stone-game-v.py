class Solution:
    def stoneGameV(self, stoneValue: list[int]) -> int:
        n = len(stoneValue)
        
        # Precompute prefix sums
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + stoneValue[i]
            
        dp = [[0] * n for _ in range(n)]
        
        # max_l[i][j] stores the max of (sum[i..k] + dp[i][k]) for k in [i..j]
        max_l = [[0] * n for _ in range(n)]
        # max_r[i][j] stores the max of (sum[k..j] + dp[k][j]) for k in [i..j]
        max_r = [[0] * n for _ in range(n)]
        
        # Base case initialization (length 1 arrays)
        for i in range(n):
            max_l[i][i] = stoneValue[i]
            max_r[i][i] = stoneValue[i]
            
        # Iterate bottom-up
        for i in range(n - 1, -1, -1):
            m = i - 1  # m is the rightmost split point where left_sum <= right_sum
            
            for j in range(i + 1, n):
                total = prefix[j + 1] - prefix[i]
                
                # Slide `m` to the right as long as the left half is <= half of the total sum
                while m + 1 < j and (prefix[m + 2] - prefix[i]) * 2 <= total:
                    m += 1
                    
                res = 0
                
                # If we have valid left splits (where left_sum < right_sum)
                if m >= i:
                    res = max(res, max_l[i][m])
                    
                left_sum = prefix[m + 1] - prefix[i]
                
                # If there's an exact tie, Alice gets to choose, so we check both sides
                if m >= i and left_sum * 2 == total:
                    res = max(res, max_r[m + 1][j])
                else:
                    # Otherwise, for points strictly right of `m`, Bob forces the right side
                    if m + 1 < j:
                        res = max(res, max_r[m + 2][j])
                        
                dp[i][j] = res
                
                # Update the running maximum caches for future states
                max_l[i][j] = max(max_l[i][j - 1], total + res)
                max_r[i][j] = max(max_r[i + 1][j], total + res)
                
        return dp[0][n - 1]