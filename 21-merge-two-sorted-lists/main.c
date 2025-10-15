#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

 struct ListNode {
     int val;
     struct ListNode *next;
 };
 
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode dummyHead = { .next = NULL };
	struct ListNode* node = &dummyHead;
	while(1) {
		if (list1 == NULL && list2 == NULL) {
			return dummyHead.next;
		}
		if (list1 == NULL) {
			node->next = list2;
			return dummyHead.next;
		}
		if (list2 == NULL) {
			node->next = list1;
			return dummyHead.next;
		}

		if (list1->val < list2->val) {
			node->next = list1;
			list1 = list1->next;
		} else {
			node->next = list2;
			list2 = list2->next;
		}

		node = node->next;
	}

	return dummyHead.next;
}

int main(int argc, char** argv) {
	int n, m;
	scanf("%d", &n);
	scanf("%d", &n);

	return 0;
}
