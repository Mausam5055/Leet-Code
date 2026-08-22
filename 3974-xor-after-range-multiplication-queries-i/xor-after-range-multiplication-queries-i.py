from typing import List

class Solution:
    def xorAfterQueries(self, nums: List[int], queries: List[List[int]]) -> int:
        MOD = 10**9 + 7
        
        # Process each query
        for l, r, k, v in queries:
            # range(start, stop, step) handles the ki jumps perfectly
            for i in range(l, r + 1, k):
                nums[i] = (nums[i] * v) % MOD
                
        # Calculate the final bitwise XOR
        ans = 0
        for num in nums:
            ans ^= num
            
        return ans