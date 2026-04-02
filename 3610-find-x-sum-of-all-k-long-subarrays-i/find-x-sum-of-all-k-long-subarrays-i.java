class Solution {
    public int[] findXSum(int[] nums, int k, int x) {
        int n = nums.length;
        int[] result = new int[n - k + 1];

        for (int i = 0; i <= n - k; i++) {

            // Step 1: count frequency
            int[] freq = new int[51]; // since nums[i] <= 50

            for (int j = i; j < i + k; j++) {
                freq[nums[j]]++;
            }

            // Step 2: store elements
            List<int[]> list = new ArrayList<>();
            for (int num = 1; num <= 50; num++) {
                if (freq[num] > 0) {
                    list.add(new int[]{num, freq[num]});
                }
            }

            // Step 3: sort
            list.sort((a, b) -> {
                if (b[1] != a[1]) return b[1] - a[1]; // freq desc
                return b[0] - a[0]; // value desc
            });

            // Step 4: take top x
            int sum = 0;
            int count = 0;

            for (int[] pair : list) {
                if (count == x) break;

                int num = pair[0];
                int f = pair[1];

                sum += num * f;
                count++;
            }

            result[i] = sum;
        }

        return result;
    }
}