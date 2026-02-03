class Solution {
    public ListNode reverseKGroup(ListNode head, int k) {
        if (head == null || k == 1) return head;

        // Dummy node before head
        ListNode dummy = new ListNode(-1);
        dummy.next = head;

        ListNode prevGroupEnd = dummy;

        while (true) {
            // 1️⃣ Find the k-th node
            ListNode kth = getKthNode(prevGroupEnd, k);
            if (kth == null) break; // not enough nodes left

            ListNode nextGroupStart = kth.next;

            // 2️⃣ Reverse k nodes
            ListNode prev = nextGroupStart;
            ListNode curr = prevGroupEnd.next;

            while (curr != nextGroupStart) {
                ListNode temp = curr.next;
                curr.next = prev;
                prev = curr;
                curr = temp;
            }

            // 3️⃣ Connect reversed group
            ListNode newGroupStart = kth;
            ListNode oldGroupStart = prevGroupEnd.next;

            prevGroupEnd.next = newGroupStart;
            prevGroupEnd = oldGroupStart;
        }

        return dummy.next;
    }

    // Helper to get k-th node from current position
    private ListNode getKthNode(ListNode curr, int k) {
        while (curr != null && k > 0) {
            curr = curr.next;
            k--;
        }
        return curr;
    }
}
