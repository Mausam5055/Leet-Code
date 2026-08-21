from math import gcd
from functools import reduce

class Solution:
    def findKthSmallest(self, coins: list[int], k: int) -> int:
        n = len(coins)

        def lcm(a, b):
            return a // gcd(a, b) * b

        def count(x):
            total = 0

            for mask in range(1, 1 << n):
                curr_lcm = 1
                bits = 0

                for i in range(n):
                    if mask & (1 << i):
                        curr_lcm = lcm(curr_lcm, coins[i])
                        bits += 1

                        # No multiples <= x
                        if curr_lcm > x:
                            break
                else:
                    if bits % 2 == 1:
                        total += x // curr_lcm
                    else:
                        total -= x // curr_lcm

            return total

        low = 1
        high = min(coins) * k

        while low < high:
            mid = (low + high) // 2

            if count(mid) >= k:
                high = mid
            else:
                low = mid + 1

        return low