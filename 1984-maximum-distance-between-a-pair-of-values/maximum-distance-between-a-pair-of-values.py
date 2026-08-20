class Solution:
    def maxDistance(self, nums1: list[int], nums2: list[int]) -> int:
        i, j = 0, 0
        max_dist = 0
        
        while i < len(nums1) and j < len(nums2):
            # If the current pair is valid, calculate the distance and try to find a larger one by advancing j
            if nums1[i] <= nums2[j]:
                max_dist = max(max_dist, j - i)
                j += 1
            # If the current pair is invalid, nums1[i] is too big. 
            # We must move to a smaller number in nums1 by advancing i.
            else:
                i += 1
                # The problem requires i <= j. If i overtakes j, we move j forward to catch up.
                if i > j:
                    j = i
                    
        return max_dist