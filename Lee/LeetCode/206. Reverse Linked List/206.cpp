#include <cstddef>

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
    ListNode* reverseList(ListNode* head)
    {
        if (head == nullptr)
            return head;

        auto new_head = head;

        for (auto node = head->next; node != nullptr;)
        {
            auto next = node->next;
            node->next = new_head;
            new_head = node;
            node = next;
        }

        head->next = nullptr;
        return new_head;
    }
};
