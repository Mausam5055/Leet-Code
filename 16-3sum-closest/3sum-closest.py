class Solution:
    def threeSumClosest(self, nums, target):
        nums.sort()
        closest = float('inf')

        for i in range(len(nums)):
            l, r = i + 1, len(nums) - 1
            
            while l < r:
                s = nums[i] + nums[l] + nums[r]

                # Update closest if better
                if abs(s - target) < abs(closest - target):
                    closest = s

                if s < target:
                    l += 1
                elif s > target:
                    r -= 1
                else:
                    return s  # exact match → can't get closer than this

        return closest
