class Solution:
    def lexGreaterPermutation(self, s: str, target: str) -> str:
        cnt = [0] * 26

        for ch in s:
            cnt[ord(ch) - ord('a')] += 1

        prefix = []
        answer = ""

        for i in range(len(target)):
            x = ord(target[i]) - ord('a')

            # Find the smallest available character greater than target[i]
            for c in range(x + 1, 26):
                if cnt[c] > 0:
                    temp = prefix + [chr(c + ord('a'))]

                    remaining = cnt[:]
                    remaining[c] -= 1

                    # Append remaining characters in sorted order
                    for j in range(26):
                        temp.extend(chr(j + ord('a')) * remaining[j])

                    answer = ''.join(temp)
                    break

            # Try to continue matching target
            if cnt[x] == 0:
                break

            cnt[x] -= 1
            prefix.append(target[i])

        return answer