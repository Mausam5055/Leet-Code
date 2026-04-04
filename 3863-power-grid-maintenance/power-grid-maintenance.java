import java.util.*;

class Solution {
    public int[] processQueries(int c, int[][] connections, int[][] queries) {
        
        // DSU setup
        int[] parent = new int[c + 1];
        for (int i = 1; i <= c; i++) parent[i] = i;

        // Find with path compression
        java.util.function.IntUnaryOperator find = new java.util.function.IntUnaryOperator() {
            public int applyAsInt(int x) {
                if (parent[x] != x)
                    parent[x] = applyAsInt(parent[x]);
                return parent[x];
            }
        };

        // Union
        for (int[] conn : connections) {
            int u = conn[0], v = conn[1];
            int pu = find.applyAsInt(u);
            int pv = find.applyAsInt(v);
            if (pu != pv) parent[pu] = pv;
        }

        // Map: root → TreeSet of active nodes
        Map<Integer, TreeSet<Integer>> map = new HashMap<>();

        for (int i = 1; i <= c; i++) {
            int root = find.applyAsInt(i);
            map.computeIfAbsent(root, k -> new TreeSet<>()).add(i);
        }

        boolean[] active = new boolean[c + 1];
        Arrays.fill(active, true);

        List<Integer> result = new ArrayList<>();

        // Process queries
        for (int[] q : queries) {
            int type = q[0], x = q[1];

            int root = find.applyAsInt(x);

            if (type == 1) {
                if (active[x]) {
                    result.add(x);
                } else {
                    TreeSet<Integer> set = map.get(root);
                    if (set.isEmpty()) result.add(-1);
                    else result.add(set.first());
                }
            } else {
                // type 2 → make offline
                if (active[x]) {
                    active[x] = false;
                    map.get(root).remove(x);
                }
            }
        }

        // Convert to array
        return result.stream().mapToInt(i -> i).toArray();
    }
}