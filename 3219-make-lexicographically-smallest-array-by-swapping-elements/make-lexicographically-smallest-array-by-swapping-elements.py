class Solution:
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:
        # Pair elements with their original indices and sort by value
        sorted_nums = sorted([(num, i) for i, num in enumerate(nums)])
        
        n = len(nums)
        ans = [0] * n
        i = 0
        
        while i < n:
            # Find the boundary of the current connected component
            j = i + 1
            while j < n and sorted_nums[j][0] - sorted_nums[j-1][0] <= limit:
                j += 1
            
            # Extract the current component
            component = sorted_nums[i:j]
            
            # Extract and sort the original indices of this component
            indices = sorted([idx for val, idx in component])
            
            # Place the sorted values into the sorted original indices
            for k in range(len(component)):
                ans[indices[k]] = component[k][0]
                
            # Move to the start of the next component
            i = j
            
        return ans