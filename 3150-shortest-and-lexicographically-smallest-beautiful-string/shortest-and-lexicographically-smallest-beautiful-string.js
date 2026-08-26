var shortestBeautifulSubstring = function(s, k) {
    let left = 0;
    let ones = 0;
    let ans = "";

    for (let right = 0; right < s.length; right++) {
        if (s[right] === '1') {
            ones++;
        }

        // Too many 1s -> shrink from left
        while (ones > k) {
            if (s[left] === '1') {
                ones--;
            }
            left++;
        }

        // Exactly k ones
        if (ones === k) {

            // Remove unnecessary leading zeros
            while (s[left] === '0') {
                left++;
            }

            let candidate = s.substring(left, right + 1);

            if (
                ans === "" ||
                candidate.length < ans.length ||
                (candidate.length === ans.length && candidate < ans)
            ) {
                ans = candidate;
            }
        }
    }

    return ans;
};