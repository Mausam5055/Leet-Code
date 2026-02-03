class Solution {
    fun connect(root: Node?): Node? {
        var curr = root   // current node at current level

        while (curr != null) {
            var head: Node? = null  // head of next level
            var prev: Node? = null  // previous node on next level

            // traverse current level using next pointers
            while (curr != null) {

                // process left child
                curr.left?.let { child ->
                    if (prev != null) {
                        prev!!.next = child
                    } else {
                        head = child
                    }
                    prev = child
                }

                // process right child
                curr.right?.let { child ->
                    if (prev != null) {
                        prev!!.next = child
                    } else {
                        head = child
                    }
                    prev = child
                }

                curr = curr.next
            }

            // move to next level
            curr = head
        }

        return root
    }
}
