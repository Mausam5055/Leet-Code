class Solution:
    def smallestSubsequence(self, s: str) -> str:
        # Dictionary to keep track of the last index of every character
        last_occurrence = {c: i for i, c in enumerate(s)}
        
        stack = []
        seen = set()
        
        for i, c in enumerate(s):
            # If we've already included this character in our result, skip it
            if c in seen:
                continue
            
            # While stack is not empty, AND the current character is smaller than the top of the stack,
            # AND the character at the top of the stack appears again later in the string...
            while stack and c < stack[-1] and last_occurrence[stack[-1]] > i:
                # We can safely discard the top character for now
                removed_char = stack.pop()
                seen.remove(removed_char)
                
            # Add the current character to the stack and mark it as seen
            stack.append(c)
            seen.add(c)
            
        return "".join(stack)