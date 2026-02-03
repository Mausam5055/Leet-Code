class Solution {
    fun connect(root: Node?): Node? {
        if (root == null) return null

        // Step 1: connect left child to right child
        if (root.left != null && root.right != null) {
            root.left!!.next = root.right

            // Step 2: connect right child to next subtree
            root.right!!.next = root.next?.left
        }

        // Step 3: recurse on left and right
        connect(root.left)
        connect(root.right)

        return root
    }
}
