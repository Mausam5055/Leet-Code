class Solution {
    fun singleNumber(nums: IntArray): Int {
        var result = 0

        for (i in 0 until 32) {
            var count = 0
            for (num in nums) {
                if ((num shr i) and 1 == 1) {
                    count++
                }
            }
            if (count % 3 != 0) {
                result = result or (1 shl i)
            }
        }
        return result
    }
}
