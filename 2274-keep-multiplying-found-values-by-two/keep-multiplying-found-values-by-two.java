import java.util.*;

class Solution {
    public int findFinalValue(int[] nums, int original) {
        Set<Integer> set = new HashSet<>();
        
        // Store all elements
        for (int num : nums) {
            set.add(num);
        }
        
        // Keep doubling
        while (set.contains(original)) {
            original *= 2;
        }
        
        return original;
    }
}