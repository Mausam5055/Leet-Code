class Solution {
  List<List<int>> subsetsWithDup(List<int> nums) {
    /*
      Step 1: Sort the array
      This is REQUIRED to handle duplicates correctly
      Example: [2,1,2] → [1,2,2]
    */
    nums.sort();

    // This will store all unique subsets
    List<List<int>> result = [];

    // Temporary list to build subsets
    List<int> current = [];

    /*
      Backtracking function
      start → index from where we can pick elements
    */
    void backtrack(int start) {
      /*
        Every recursive call adds the current subset
        because every prefix is a valid subset
      */
      result.add(List.from(current));

      /*
        Try adding each element starting from 'start'
      */
      for (int i = start; i < nums.length; i++) {

        /*
          Skip duplicates:
          If current element is same as previous
          AND we are at the same recursion level,
          then skip to avoid duplicate subsets
        */
        if (i > start && nums[i] == nums[i - 1]) continue;

        // Choose the current element
        current.add(nums[i]);

        // Recurse to build further subsets
        backtrack(i + 1);

        // Backtrack (remove last element)
        current.removeLast();
      }
    }

    // Start backtracking from index 0
    backtrack(0);

    return result;
  }
}
