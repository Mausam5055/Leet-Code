class Solution {
    public int minOperations(int[] nums) {
        Stack<Integer> stack = new Stack<>();
        int operations = 0;

        for (int num : nums) {
            while (!stack.isEmpty() && stack.peek() > num) {
                stack.pop();
            }

            if (num > 0 && (stack.isEmpty() || stack.peek() < num)) {
                operations++;
                stack.push(num);
            }
        }

        return operations;
    }
}