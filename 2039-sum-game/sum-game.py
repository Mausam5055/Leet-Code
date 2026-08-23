class Solution:
    def sumGame(self, num: str) -> bool:
        n = len(num)
        
        sum1, sum2 = 0, 0
        count1, count2 = 0, 0
        
        # Calculate sums and '?' counts for the first half
        for i in range(n // 2):
            if num[i] == '?':
                count1 += 1
            else:
                sum1 += int(num[i])
                
        # Calculate sums and '?' counts for the second half
        for i in range(n // 2, n):
            if num[i] == '?':
                count2 += 1
            else:
                sum2 += int(num[i])
                
        # Bob wins only if the sums and '?' distributions perfectly balance out
        return (sum1 - sum2) + 9 * (count1 - count2) / 2 != 0