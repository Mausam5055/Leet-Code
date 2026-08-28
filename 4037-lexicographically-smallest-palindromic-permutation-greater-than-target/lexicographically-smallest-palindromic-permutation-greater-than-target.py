from collections import Counter

class Solution:
    def lexPalindromicPermutation(self, s: str, target: str) -> str:
        n = len(s)
        counts = Counter(s)
        
        # 1. Check if a palindrome is even possible
        odd_chars = [ch for ch, freq in counts.items() if freq % 2 == 1]
        if len(odd_chars) > 1:
            return ""
            
        mid_char = odd_chars[0] if odd_chars else ""
        
        # Pool of characters available to build the first half of the palindrome
        half_pool = []
        for ch, freq in counts.items():
            half_pool.extend([ch] * (freq // 2))
            
        N = n // 2
        target_prefix = target[:N]
        
        half_counts = Counter(half_pool)
        target_counts = Counter(target_prefix)
        
        # 2. Case 1: Try to exactly match the target's first half
        if half_counts == target_counts:
            cand = target_prefix + mid_char + target_prefix[::-1]
            if cand > target:
                return cand
                
        # 3. Case 2: Diverge from target_prefix as late as possible
        for i in range(N - 1, -1, -1):
            req_counts = Counter(target_prefix[:i])
            
            # Check if we possess the characters to form target_prefix[:i]
            can_form = True
            for ch, count in req_counts.items():
                if half_counts[ch] < count:
                    can_form = False
                    break
                    
            if not can_form:
                continue
                
            # Remaining characters available after fulfilling target_prefix[:i]
            rem_counts = half_counts - req_counts
            target_char = target_prefix[i]
            
            # Find the smallest available character strictly greater than target_prefix[i]
            valid_chars = [ch for ch in rem_counts if ch > target_char and rem_counts[ch] > 0]
            
            if valid_chars:
                best_c = min(valid_chars)
                rem_counts[best_c] -= 1
                
                # The rest of the prefix is sorted in ascending order to be as small as possible
                suffix_chars = []
                for ch in sorted(rem_counts.keys()):
                    suffix_chars.extend([ch] * rem_counts[ch])
                    
                suffix = "".join(suffix_chars)
                prefix = target_prefix[:i] + best_c + suffix
                
                # Construct the full palindrome
                cand = prefix + mid_char + prefix[::-1]
                return cand
                
        # If no valid strictly greater palindromic permutation exists
        return ""