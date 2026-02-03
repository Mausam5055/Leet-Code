class Solution {

    // Map to store value -> index of inorder array
    Map<Integer, Integer> inorderMap = new HashMap<>();
    
    // Pointer for postorder traversal
    int postIndex;

    public TreeNode buildTree(int[] inorder, int[] postorder) {
        postIndex = postorder.length - 1;

        // Store inorder values with indices
        for (int i = 0; i < inorder.length; i++) {
            inorderMap.put(inorder[i], i);
        }

        return build(inorder, postorder, 0, inorder.length - 1);
    }

    private TreeNode build(int[] inorder, int[] postorder, int left, int right) {
        // Base case
        if (left > right) return null;

        // Pick root from postorder
        int rootVal = postorder[postIndex--];
        TreeNode root = new TreeNode(rootVal);

        // Find root index in inorder
        int index = inorderMap.get(rootVal);

        // IMPORTANT: build right subtree first
        root.right = build(inorder, postorder, index + 1, right);
        root.left = build(inorder, postorder, left, index - 1);

        return root;
    }
}
