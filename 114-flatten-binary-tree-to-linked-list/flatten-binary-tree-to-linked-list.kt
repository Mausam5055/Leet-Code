class Solution {
    fun flatten(root: TreeNode?) {
        var curr = root

        while (curr != null) {
            if (curr.left != null) {
                // prev is NON-null here
                var prev: TreeNode = curr.left!!

                // find rightmost node
                while (prev.right != null) {
                    prev = prev.right!!
                }

                // attach right subtree
                prev.right = curr.right

                // move left subtree to right
                curr.right = curr.left
                curr.left = null
            }
            curr = curr.right
        }
    }
}
