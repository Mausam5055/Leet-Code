class Solution {
    public int maxBottlesDrunk(int numBottles, int numExchange) {

        int drunk = numBottles;
        int empty = numBottles;

        while (empty >= numExchange) {

            // exchange empty bottles for 1 full bottle
            empty -= numExchange;

            // drink it → becomes empty again
            empty += 1;

            drunk += 1;

            // exchange requirement increases
            numExchange++;
        }

        return drunk;
    }
}