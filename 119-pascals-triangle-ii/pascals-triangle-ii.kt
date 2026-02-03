class Solution {
    fun getRow(rowIndex: Int): List<Int> {

        val row = MutableList(rowIndex + 1) { 0 }
        row[0] = 1

        for (i in 1..rowIndex) {
            for (j in i downTo 1) {
                row[j] = row[j] + row[j - 1]
            }
        }

        return row
    }
}
