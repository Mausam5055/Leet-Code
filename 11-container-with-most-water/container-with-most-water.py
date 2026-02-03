class Solution:
    def maxArea(self, height):
        l, r = 0, len(height) - 1
        max_area = 0
        
        while l < r:
            h = min(height[l], height[r])
            area = h * (r - l)
            if area > max_area:
                max_area = area
            
            # move the shorter pointer
            if height[l] < height[r]:
                l += 1
            else:
                r -= 1
        
        return max_area
