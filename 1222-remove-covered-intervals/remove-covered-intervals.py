class Solution:
    def removeCoveredIntervals(self, intervals: list[list[int]]) -> int:
        # Sort by start point (ascending), then by end point (descending)
        intervals.sort(key=lambda x: (x[0], -x[1]))
        
        remaining_count = 0
        max_end = -1
        
        for start, end in intervals:
            # If the current interval extends beyond the maximum end we've seen,
            # it is not covered.
            if end > max_end:
                remaining_count += 1
                max_end = end
                
        return remaining_count