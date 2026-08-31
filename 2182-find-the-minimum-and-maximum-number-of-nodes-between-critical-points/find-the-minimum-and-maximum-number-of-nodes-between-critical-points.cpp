/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        // A list must have at least 3 nodes to have any critical points
        if (!head || !head->next || !head->next->next) {
            return {-1, -1};
        }

        ListNode* prev = head;
        ListNode* curr = head->next;
        ListNode* nxt = curr->next;

        int first_crit = -1;
        int last_crit = -1;
        int min_dist = INT_MAX;
        
        int currentIndex = 1; // Index of the 'curr' node

        while (nxt != nullptr) {
            // Check if current node is a local maxima or minima
            bool is_maxima = (curr->val > prev->val) && (curr->val > nxt->val);
            bool is_minima = (curr->val < prev->val) && (curr->val < nxt->val);

            if (is_maxima || is_minima) {
                if (first_crit == -1) {
                    // This is the very first critical point we've found
                    first_crit = currentIndex;
                } else {
                    // Compare the gap between the current and the last found critical point
                    min_dist = min(min_dist, currentIndex - last_crit);
                }
                // Update the last critical point to the current one
                last_crit = currentIndex;
            }

            // Move pointers forward
            prev = curr;
            curr = nxt;
            nxt = nxt->next;
            currentIndex++;
        }

        // If min_dist is still INT_MAX, we found fewer than 2 critical points
        if (min_dist == INT_MAX) {
            return {-1, -1};
        }

        // max_dist is always the difference between the last and first critical points
        int max_dist = last_crit - first_crit;
        
        return {min_dist, max_dist};
    }
};