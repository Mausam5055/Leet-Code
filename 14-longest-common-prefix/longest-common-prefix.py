class Solution:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        # Edge case: if the list is empty
        if not strs:
            return ""
        
        # 1. Sort the list of strings alphabetically
        strs.sort()
        
        # 2. Compare only the first and the last string
        # Because the list is sorted, these two are the most different.
        first = strs[0]
        last = strs[-1]
        
        idx = 0
        # Iterate while index is within bounds of both strings
        while idx < len(first) and idx < len(last):
            if first[idx] == last[idx]:
                idx += 1
            else:
                break
                
        # Return the prefix up to the mismatch
        return first[:idx]  