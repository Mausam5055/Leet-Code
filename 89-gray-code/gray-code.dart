class Solution {
  List<int> grayCode(int n) {
    /*
      Total numbers in an n-bit Gray Code sequence = 2^n
      Example:
        n = 2 → 2^2 = 4 numbers
        n = 3 → 2^3 = 8 numbers
    */
    int size = 1 << n; // 2^n
    
    // Result list to store the gray code sequence
    List<int> result = [];
    
    /*
      Gray Code Formula:
        gray(i) = i ^ (i >> 1)
      
      Why this works:
      - XOR ensures only one bit changes between consecutive numbers
      - Right shift aligns previous bits to control transitions
    */
    for (int i = 0; i < size; i++) {
      result.add(i ^ (i >> 1));
    }
    
    return result;
  }
}
