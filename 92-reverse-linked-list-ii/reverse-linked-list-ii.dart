/**
 * Definition for singly-linked list.
 * class ListNode {
 *   int val;
 *   ListNode? next;
 *   ListNode([this.val = 0, this.next]);
 * }
 */

class Solution {
  ListNode? reverseBetween(ListNode? head, int left, int right) {
    if (head == null || left == right) return head;

    // Dummy node to handle edge case when left == 1
    ListNode dummy = ListNode(0, head);
    ListNode? prev = dummy;

    // Move prev to the node just before `left`
    for (int i = 1; i < left; i++) {
      prev = prev!.next;
    }

    // Current node is the first node to be reversed
    ListNode? curr = prev!.next;

    // Reverse the sublist
    for (int i = 0; i < right - left; i++) {
      ListNode? nextNode = curr!.next;
      curr.next = nextNode!.next;
      nextNode.next = prev.next;
      prev.next = nextNode;
    }

    return dummy.next;
  }
}
