class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        // Dummy node to handle head duplicates
        ListNode* dummy = new ListNode(0);
        dummy->next = head;

        ListNode* prev = dummy;

        while (head != nullptr) {
            // If duplicate sequence detected
            if (head->next && head->val == head->next->val) {
                int dupVal = head->val;

                // Skip all nodes with dupVal
                while (head && head->val == dupVal) {
                    head = head->next;
                }
                prev->next = head; // Remove duplicates
            } 
            else {
                // No duplicate, move prev forward
                prev = head;
                head = head->next;
            }
        }
        return dummy->next;
    }
};
