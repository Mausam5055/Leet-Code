class Solution {
    fun canCompleteCircuit(gas: IntArray, cost: IntArray): Int {
        var totalTank = 0
        var currentTank = 0
        var start = 0

        for (i in gas.indices) {
            val diff = gas[i] - cost[i]
            totalTank += diff
            currentTank += diff

            // If we can't reach next station
            if (currentTank < 0) {
                start = i + 1
                currentTank = 0
            }
        }

        return if (totalTank >= 0) start else -1
    }
}
