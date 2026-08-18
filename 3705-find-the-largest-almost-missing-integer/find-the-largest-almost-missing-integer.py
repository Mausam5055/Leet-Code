class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        count = {}

        # Check every subarray of size k
        for i in range(len(nums) - k + 1):
            seen = set()

            for j in range(i, i + k):
                seen.add(nums[j])

            # Count each number only once per subarray
            for x in seen:
                count[x] = count.get(x, 0) + 1

        ans = -1

        # Find the largest number appearing in exactly one subarray
        for x, freq in count.items():
            if freq == 1:
                ans = max(ans, x)

        return ans