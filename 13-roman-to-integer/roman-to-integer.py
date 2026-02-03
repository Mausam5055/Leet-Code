class Solution:
    def romanToInt(self, s: str) -> int:
        # 1. Create a mapping of Roman symbols to integers
        roman_map = {
            'I': 1,
            'V': 5,
            'X': 10,
            'L': 50,
            'C': 100,
            'D': 500,
            'M': 1000
        }
        
        total = 0
        n = len(s)
        
        # 2. Iterate through the string
        for i in range(n):
            current_val = roman_map[s[i]]
            
            # Check if there is a next character and compare values
            # If current value < next value, it's a subtraction case (e.g., IV)
            if i < n - 1 and current_val < roman_map[s[i+1]]:
                total -= current_val
            else:
                # Otherwise, it's standard addition
                total += current_val
                
        return total