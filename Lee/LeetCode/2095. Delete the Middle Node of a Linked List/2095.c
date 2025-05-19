#include <stdbool.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteMiddle(struct ListNode* head)
{
	struct ListNode ptb = { 0, head };

	struct ListNode* middle = &ptb;
	struct ListNode* seek = head;
	bool toggle = true;

	while (seek->next != NULL)
	{
		if (toggle)
			middle = middle->next;

		seek = seek->next;
		toggle = !toggle;
	}
	middle->next = middle->next->next;

	return ptb.next;    
}
