class Solution:
    def resultArray(self, nums: list[int]) -> list[int]:
        # Initialize the two arrays with the first two elements
        arr1 = [nums[0]]
        arr2 = [nums[1]]
        
        # Iterate through the rest of the elements starting from index 2
        for i in range(2, len(nums)):
            # Compare the last elements of arr1 and arr2
            if arr1[-1] > arr2[-1]:
                arr1.append(nums[i])
            else:
                arr2.append(nums[i])
                
        # Concatenate and return the combined result
        return arr1 + arr2