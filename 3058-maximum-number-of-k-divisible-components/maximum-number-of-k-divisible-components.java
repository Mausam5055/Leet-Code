import java.util.*;

class Solution {

    List<Integer>[] graph;
    int[] values;
    int k;
    int result = 0;

    public int maxKDivisibleComponents(int n, int[][] edges, int[] values, int k) {
        this.values = values;
        this.k = k;

        // Build graph
        graph = new ArrayList[n];
        for (int i = 0; i < n; i++) graph[i] = new ArrayList<>();

        for (int[] e : edges) {
            graph[e[0]].add(e[1]);
            graph[e[1]].add(e[0]);
        }

        dfs(0, -1);
        return result;
    }

    private long dfs(int node, int parent) {
        long sum = values[node];

        for (int nei : graph[node]) {
            if (nei == parent) continue;
            sum += dfs(nei, node);
        }

        if (sum % k == 0) {
            result++;
            return 0; // cut here
        }

        return sum;
    }
}