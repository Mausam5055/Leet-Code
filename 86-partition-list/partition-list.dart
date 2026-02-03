class Solution {
  ListNode? partition(ListNode? head, int x) {
    ListNode lessDummy = ListNode(0);
    ListNode greaterDummy = ListNode(0);

    ListNode less = lessDummy;
    ListNode greater = greaterDummy;

    while (head != null) {
      if (head.val < x) {
        less.next = head;
        less = less.next!;
      } else {
        greater.next = head;
        greater = greater.next!;
      }
      head = head.next;
    }

    // terminate greater list
    greater.next = null;

    // connect two lists
    less.next = greaterDummy.next;

    return lessDummy.next;
  }
}
