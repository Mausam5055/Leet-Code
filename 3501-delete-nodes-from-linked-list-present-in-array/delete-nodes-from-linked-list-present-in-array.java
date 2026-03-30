import java.util.HashSet;

class Solution {
    public ListNode modifiedList(int[] nums, ListNode head) {
        
        // Step 1: Put nums into set
        HashSet<Integer> set = new HashSet<>();
        for (int num : nums) {
            set.add(num);
        }
        
        // Step 2: Dummy node
        ListNode dummy = new ListNode(0);
        dummy.next = head;
        
        ListNode curr = dummy;
        
        // Step 3: Traverse
        while (curr.next != null) {
            if (set.contains(curr.next.val)) {
                // delete node
                curr.next = curr.next.next;
            } else {
                curr = curr.next;
            }
        }
        
        return dummy.next;
    }
}