class Solution {

    // Segment Tree supporting:
    // 1) Range add
    // 2) Query rightmost index where prefix == target
    class SegTree {
        int n;
        int[] min, max, lazy;

        SegTree(int[] arr) {
            n = arr.length;
            min = new int[4 * n];
            max = new int[4 * n];
            lazy = new int[4 * n];
            build(1, 0, n - 1, arr);
        }

        void build(int idx, int l, int r, int[] arr) {
            if (l == r) {
                min[idx] = max[idx] = arr[l];
                return;
            }
            int mid = (l + r) / 2;
            build(idx * 2, l, mid, arr);
            build(idx * 2 + 1, mid + 1, r, arr);
            pull(idx);
        }

        void pull(int idx) {
            min[idx] = Math.min(min[idx * 2], min[idx * 2 + 1]);
            max[idx] = Math.max(max[idx * 2], max[idx * 2 + 1]);
        }

        void apply(int idx, int val) {
            min[idx] += val;
            max[idx] += val;
            lazy[idx] += val;
        }

        void push(int idx) {
            if (lazy[idx] != 0) {
                apply(idx * 2, lazy[idx]);
                apply(idx * 2 + 1, lazy[idx]);
                lazy[idx] = 0;
            }
        }

        void rangeAdd(int idx, int l, int r, int ql, int qr, int val) {
            if (ql > r || qr < l) return;
            if (ql <= l && r <= qr) {
                apply(idx, val);
                return;
            }
            push(idx);
            int mid = (l + r) / 2;
            rangeAdd(idx * 2, l, mid, ql, qr, val);
            rangeAdd(idx * 2 + 1, mid + 1, r, ql, qr, val);
            pull(idx);
        }

        int findRightmost(int idx, int l, int r, int ql, int qr, int target) {
            if (ql > r || qr < l) return -1;
            if (min[idx] > target || max[idx] < target) return -1;
            if (l == r) return l;

            push(idx);
            int mid = (l + r) / 2;

            int res = findRightmost(idx * 2 + 1, mid + 1, r, ql, qr, target);
            if (res != -1) return res;
            return findRightmost(idx * 2, l, mid, ql, qr, target);
        }

        int pointQuery(int idx, int l, int r, int pos) {
            if (l == r) return min[idx];
            push(idx);
            int mid = (l + r) / 2;
            if (pos <= mid) return pointQuery(idx * 2, l, mid, pos);
            return pointQuery(idx * 2 + 1, mid + 1, r, pos);
        }
    }

    public int longestBalanced(int[] nums) {
        int n = nums.length;

        Map<Integer, List<Integer>> pos = new HashMap<>();
        for (int i = 0; i < n; i++) {
            pos.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }

        int[] contrib = new int[n];
        for (var e : pos.entrySet()) {
            int v = e.getKey();
            int first = e.getValue().get(0);
            contrib[first] = (v % 2 == 0) ? 1 : -1;
        }

        int[] pref = new int[n];
        pref[0] = contrib[0];
        for (int i = 1; i < n; i++) {
            pref[i] = pref[i - 1] + contrib[i];
        }

        SegTree seg = new SegTree(pref);

        Map<Integer, Integer> ptr = new HashMap<>();
        int res = 0;

        for (int l = 0; l < n; l++) {
            if (n - l <= res) break;

            int target = (l == 0) ? 0 : seg.pointQuery(1, 0, n - 1, l - 1);
            int r = seg.findRightmost(1, 0, n - 1, l, n - 1, target);
            if (r != -1) {
                res = Math.max(res, r - l + 1);
            }

            int val = nums[l];
            int pidx = ptr.getOrDefault(val, 0);
            List<Integer> list = pos.get(val);

            int p = list.get(pidx);
            int q = (pidx + 1 < list.size()) ? list.get(pidx + 1) : n;

            int sign = (val % 2 == 0) ? 1 : -1;
            seg.rangeAdd(1, 0, n - 1, p, q - 1, -sign);

            ptr.put(val, pidx + 1);
        }

        return res;
    }
}
