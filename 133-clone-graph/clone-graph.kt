class Solution {

    private val map = HashMap<Node, Node>()

    fun cloneGraph(node: Node?): Node? {
        if (node == null) return null

        // If already cloned, return it
        if (map.containsKey(node)) {
            return map[node]
        }

        // Clone the current node
        val clone = Node(node.`val`)
        map[node] = clone

        // Clone neighbors
        for (neighbor in node.neighbors) {
            clone.neighbors.add(cloneGraph(neighbor))
        }

        return clone
    }
}
