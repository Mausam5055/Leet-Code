class Solution {
    public ListNode insertionSortList(ListNode head) {
        if (head == null || head.next == null) return head;

        ListNode dummy = new ListNode(0); // start of sorted list
        ListNode curr = head;

        while (curr != null) {
            ListNode nextNode = curr.next; // save next node

            // find position to insert current node
            ListNode prev = dummy;
            while (prev.next != null && prev.next.val < curr.val) {
                prev = prev.next;
            }

            // insert curr between prev and prev.next
            curr.next = prev.next;
            prev.next = curr;

            curr = nextNode; // move to next node in original list
        }

        return dummy.next;
    }
}
