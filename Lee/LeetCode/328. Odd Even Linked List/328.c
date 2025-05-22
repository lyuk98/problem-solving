#include <stdbool.h>
#include <stddef.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* oddEvenList(struct ListNode* head)
{
    if (head == NULL)
        return head;
    else if (head->next == NULL)
        return head;

    struct ListNode* odd = head;
    struct ListNode* even = odd->next;

    struct ListNode* so = odd;
    struct ListNode* se = even;
    struct ListNode* seek = even->next;

    so->next = NULL;
    se->next = NULL;
    bool is_even = false;

    while (seek != NULL)
    {
        if (is_even)
        {
            se->next = seek;
            se = se->next;
            seek = seek->next;
            se->next = NULL;
        }
        else
        {
            so->next = seek;
            so = so->next;
            seek = seek->next;
            so->next = NULL;
        }

        is_even = !is_even;
    }
    so->next = even;

    return odd;
}
