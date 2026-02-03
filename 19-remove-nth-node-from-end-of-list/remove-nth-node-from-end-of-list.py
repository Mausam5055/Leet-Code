from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        # Dummy helps handle removing the head
        dummy = ListNode(0, head)
        fast = dummy
        slow = dummy

        # Move fast n+1 steps ahead so slow ends up before the node to remove
        for _ in range(n + 1):
            fast = fast.next

        # Move both until fast reaches the end
        while fast:
            fast = fast.next
            slow = slow.next

        # Remove the target node
        slow.next = slow.next.next

        return dummy.next

# ---------- Helpers for local testing (optional) ----------
def build_list(arr):
    dummy = ListNode(0)
    cur = dummy
    for v in arr:
        cur.next = ListNode(v)
        cur = cur.next
    return dummy.next

def to_list(head):
    out = []
    cur = head
    while cur:
        out.append(cur.val)
        cur = cur.next
    return out

# ---------- Example tests ----------
if __name__ == "__main__":
    s = Solution()

    head = build_list([1,2,3,4,5])
    res = s.removeNthFromEnd(head, 2)
    print(to_list(res))   # -> [1,2,3,5]

    head = build_list([1])
    res = s.removeNthFromEnd(head, 1)
    print(to_list(res))   # -> []

    head = build_list([1,2])
    res = s.removeNthFromEnd(head, 1)
    print(to_list(res))   # -> [1]
