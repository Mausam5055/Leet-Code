import java.util.*;

class Solution {
    public int maximizeSquareHoleArea(int n, int m, int[] hBars, int[] vBars) {
        int hMax = getMaxConsecutive(hBars);
        int vMax = getMaxConsecutive(vBars);
        
        int side = Math.min(hMax, vMax) + 1;
        return side * side;
    }
    
    private int getMaxConsecutive(int[] arr) {
        Arrays.sort(arr);
        
        int max = 1, curr = 1;
        
        for(int i = 1; i < arr.length; i++) {
            if(arr[i] == arr[i - 1] + 1) {
                curr++;
            } else {
                curr = 1;
            }
            max = Math.max(max, curr);
        }
        
        return max;
    }
}