function searchRange(nums: number[], target: number): number[] {
    const first = findFirst(nums, target);
    const last = findLast(nums, target);
    return [first, last];
}

function findFirst(nums: number[], target: number): number {
    let low = 0;
    let high = nums.length - 1;
    let ans = -1;

    while (low <= high) {
        const mid = Math.floor(low + (high - low) / 2);

        if (nums[mid] === target) {
            ans = mid;
            high = mid - 1; // move left
        } else if (nums[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

function findLast(nums: number[], target: number): number {
    let low = 0;
    let high = nums.length - 1;
    let ans = -1;

    while (low <= high) {
        const mid = Math.floor(low + (high - low) / 2);

        if (nums[mid] === target) {
            ans = mid;
            low = mid + 1; // move right
        } else if (nums[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}
