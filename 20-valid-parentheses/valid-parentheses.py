class Solution:
    def isValid(self, s: str) -> bool:
        stack = []
        close_map = {')': '(', ']': '[', '}': '{'}
        
        for char in s:
            # If it's a closing bracket
            if char in close_map:
                # Stack empty or not matching
                if not stack or stack[-1] != close_map[char]:
                    return False
                stack.pop()
            else:
                # Opening bracket → push on stack
                stack.append(char)
        
        # Valid if no unmatched opening brackets remain
        return len(stack) == 0
