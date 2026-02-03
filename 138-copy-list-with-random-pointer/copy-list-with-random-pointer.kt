class Solution {
    fun copyRandomList(head: Node?): Node? {
        if (head == null) return null

        val map = HashMap<Node, Node>()
        var curr = head

        // Step 1: create copy of each node
        while (curr != null) {
            map[curr] = Node(curr.`val`)
            curr = curr.next
        }

        curr = head

        // Step 2: assign next & random pointers
        while (curr != null) {
            map[curr]!!.next = map[curr.next]
            map[curr]!!.random = map[curr.random]
            curr = curr.next
        }

        return map[head]
    }
}
