function searchInsert(nums: number[], target: number): number {
    let low = 0;
    let high = nums.length - 1;

    while (low <= high) {
        const mid = Math.floor(low + (high - low) / 2);

        if (nums[mid] === target) {
            return mid;        // target found
        } else if (nums[mid] < target) {
            low = mid + 1;     // move right
        } else {
            high = mid - 1;    // move left
        }
    }

    // insertion position
    return low;
}
