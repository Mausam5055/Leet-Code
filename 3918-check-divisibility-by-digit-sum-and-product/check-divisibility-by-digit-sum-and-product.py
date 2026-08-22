class Solution:
    def checkDivisibility(self, n: int) -> bool:
        temp = n
        digit_sum = 0
        digit_product = 1
        
        # Extract digits one by one
        while temp > 0:
            digit = temp % 10
            digit_sum += digit
            digit_product *= digit
            temp //= 10
            
        # Check if n is divisible by their sum
        total_sum = digit_sum + digit_product
        return n % total_sum == 0