class Solution {
    public int findClosest(int x, int y, int z) {
        int d1 = Math.abs(x - z); // distance of Person 1
        int d2 = Math.abs(y - z); // distance of Person 2
        
        if (d1 < d2) return 1;
        if (d2 < d1) return 2;
        return 0; // both reach at same time
    }
}
