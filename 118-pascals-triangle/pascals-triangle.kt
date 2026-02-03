class Solution {
    fun generate(numRows: Int): List<List<Int>> {

        val result = mutableListOf<List<Int>>()

        for (i in 0 until numRows) {
            val row = mutableListOf<Int>()

            for (j in 0..i) {
                if (j == 0 || j == i) {
                    row.add(1)
                } else {
                    val prevRow = result[i - 1]
                    row.add(prevRow[j - 1] + prevRow[j])
                }
            }

            result.add(row)
        }

        return result
    }
}
