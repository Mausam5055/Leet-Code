import java.util.*;

class Solution {
    public List<Integer> survivedRobotsHealths(int[] positions, int[] healths, String directions) {
        int n = positions.length;
        Integer[] indices = new Integer[n];
        
        // Initialize indices 0 to n-1
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }

        // Sort indices based on the robots' positions on the line
        Arrays.sort(indices, (i, j) -> Integer.compare(positions[i], positions[j]));

        Stack<Integer> stack = new Stack<>();

        // Process robots from left to right
        for (int curr : indices) {
            // If moving right, it might collide with future 'L' robots, so add to stack
            if (directions.charAt(curr) == 'R') {
                stack.push(curr);
            } else {
                // If moving left, resolve collisions with any 'R' robots in the stack
                while (!stack.isEmpty() && directions.charAt(stack.peek()) == 'R' && healths[curr] > 0) {
                    int top = stack.peek();
                    
                    if (healths[curr] > healths[top]) {
                        healths[curr] -= 1;   // Current robot takes 1 damage
                        healths[top] = 0;     // Top robot is destroyed
                        stack.pop();
                    } else if (healths[curr] < healths[top]) {
                        healths[top] -= 1;    // Top robot takes 1 damage
                        healths[curr] = 0;    // Current robot is destroyed
                    } else {
                        // Both have equal health and destroy each other
                        healths[curr] = 0;
                        healths[top] = 0;
                        stack.pop();
                    }
                }
                
                // If the 'L' robot survived all collisions, it continues moving left harmlessly
                if (healths[curr] > 0) {
                    stack.push(curr);
                }
            }
        }

        // Collect the surviving robots' healths in their original given order
        List<Integer> result = new ArrayList<>();
        for (int h : healths) {
            if (h > 0) {
                result.add(h);
            }
        }
        
        return result;
    }
}