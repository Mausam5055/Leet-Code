class Solution {
    public char nextGreatestLetter(char[] letters, char target) {
        int left = 0, right = letters.length - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (letters[mid] <= target) {
                left = mid + 1;   // move right to find a greater letter
            } else {
                right = mid - 1;  // possible answer, but try smaller index
            }
        }
        
        // If left is within bounds, it's the answer
        // Otherwise wrap around to the first letter
        return letters[left % letters.length];
    }
}
