import java.util.Stack;

class Solution {
    public int evalRPN(String[] tokens) {
        Stack<Integer> stack = new Stack<>();

        for (String token : tokens) {
            // If token is an operator
            if (token.equals("+") || token.equals("-") || 
                token.equals("*") || token.equals("/")) {
                
                int b = stack.pop(); // second operand
                int a = stack.pop(); // first operand
                
                int result = 0;
                
                switch (token) {
                    case "+":
                        result = a + b;
                        break;
                    case "-":
                        result = a - b;
                        break;
                    case "*":
                        result = a * b;
                        break;
                    case "/":
                        result = a / b; // truncates toward 0
                        break;
                }
                
                stack.push(result);
            } 
            // If token is a number
            else {
                stack.push(Integer.parseInt(token));
            }
        }
        
        return stack.pop(); // final answer
    }
}
