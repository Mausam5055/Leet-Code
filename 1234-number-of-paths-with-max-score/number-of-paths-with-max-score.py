class Solution:
    def pathsWithMaxScore(self, board: list[str]) -> list[int]:
        n = len(board)
        MOD = 10**9 + 7
        
        # dp_score tracks the max score to reach a cell. -1 means unreachable.
        dp_score = [[-1] * n for _ in range(n)]
        # dp_ways tracks the number of ways to achieve the max score.
        dp_ways = [[0] * n for _ in range(n)]
        
        # Base case: Starting point at the bottom right
        dp_score[n-1][n-1] = 0
        dp_ways[n-1][n-1] = 1
        
        # Iterate from bottom-right up to top-left
        for r in range(n - 1, -1, -1):
            for c in range(n - 1, -1, -1):
                # Skip the starting cell and any obstacles
                if (r == n - 1 and c == n - 1) or board[r][c] == 'X':
                    continue
                    
                # 1. Find the maximum score from the 3 possible prior directions
                max_prev_score = -1
                if r + 1 < n:
                    max_prev_score = max(max_prev_score, dp_score[r+1][c])
                if c + 1 < n:
                    max_prev_score = max(max_prev_score, dp_score[r][c+1])
                if r + 1 < n and c + 1 < n:
                    max_prev_score = max(max_prev_score, dp_score[r+1][c+1])
                    
                # If all previous cells are unreachable, this cell is also unreachable
                if max_prev_score == -1:
                    continue
                    
                # 2. Update the max score for the current cell
                # 'E' counts as 0, otherwise convert the string digit to an integer
                val = 0 if board[r][c] == 'E' else int(board[r][c])
                dp_score[r][c] = max_prev_score + val
                
                # 3. Sum the ways from directions that provided the maximum score
                ways = 0
                if r + 1 < n and dp_score[r+1][c] == max_prev_score:
                    ways = (ways + dp_ways[r+1][c]) % MOD
                if c + 1 < n and dp_score[r][c+1] == max_prev_score:
                    ways = (ways + dp_ways[r][c+1]) % MOD
                if r + 1 < n and c + 1 < n and dp_score[r+1][c+1] == max_prev_score:
                    ways = (ways + dp_ways[r+1][c+1]) % MOD
                    
                dp_ways[r][c] = ways
                
        # If the destination cell is completely unreachable, return [0, 0]
        if dp_ways[0][0] == 0:
            return [0, 0]
        
        return [dp_score[0][0], dp_ways[0][0]]