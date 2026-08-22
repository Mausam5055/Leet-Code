import collections
from typing import List

class Solution:
    def minJumps(self, arr: List[int]) -> int:
        n = len(arr)
        # Base case: if array has only 1 element, we're already at the end.
        if n <= 1:
            return 0
        
        # Dictionary to store value -> list of indices
        graph = collections.defaultdict(list)
        for i, val in enumerate(arr):
            graph[val].append(i)
            
        # Initialize BFS
        queue = collections.deque([0])  # store index
        visited = {0}
        steps = 0
        
        while queue:
            # Level-by-level traversal
            for _ in range(len(queue)):
                curr = queue.popleft()
                
                # If we've reached the last index, return the step count
                if curr == n - 1:
                    return steps
                
                # Gather all possible next indices: j (same value), i-1, i+1
                neighbors = graph[arr[curr]]
                neighbors.append(curr - 1)
                neighbors.append(curr + 1)
                
                # Check bounds and if visited
                for nxt in neighbors:
                    if 0 <= nxt < n and nxt not in visited:
                        visited.add(nxt)
                        queue.append(nxt)
                
                # CRITICAL STEP: Clear the teleport list for this value. 
                # This prevents O(N^2) worst-case scenarios and avoids TLE.
                graph[arr[curr]].clear()
                
            steps += 1
            
        return -1