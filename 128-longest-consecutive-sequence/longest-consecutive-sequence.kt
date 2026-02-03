class Solution {
    fun longestConsecutive(nums: IntArray): Int {

        val set = nums.toHashSet()
        var longest = 0

        for (num in set) {
            // Only start counting if num is the beginning of a sequence
            if (!set.contains(num - 1)) {
                var currentNum = num
                var count = 1

                while (set.contains(currentNum + 1)) {
                    currentNum++
                    count++
                }

                longest = maxOf(longest, count)
            }
        }
        return longest
    }
}
