class Solution {
    public ListNode swapPairs(ListNode head) {
        // Dummy node to simplify head manipulation
        ListNode dummy = new ListNode(-1);
        dummy.next = head;

        ListNode prev = dummy;

        while (prev.next != null && prev.next.next != null) {
            ListNode a = prev.next;
            ListNode b = prev.next.next;

            // Swapping nodes
            a.next = b.next;
            b.next = a;
            prev.next = b;

            // Move prev pointer for next swaps
            prev = a;
        }

        return dummy.next;
    }
}
