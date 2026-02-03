class Solution {
    fun singleNumber(nums: IntArray): Int {
        var ans = 0
        for (num in nums) {
            ans = ans xor num
        }
        return ans
    }
}
