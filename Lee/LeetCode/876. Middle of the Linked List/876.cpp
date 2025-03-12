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

class Solution
{
public:
    ListNode* middleNode(ListNode* head)
    {
        bool even = true;
        auto midpoint = head;
        
        for(; head; head = head->next)
        {
            if((even = !even))
                midpoint = midpoint->next;
        }

        return midpoint;
    }
};
