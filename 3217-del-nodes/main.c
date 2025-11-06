#include "..\readargs.h"
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

#define MAX_SIZE 100000
_Bool map[MAX_SIZE] = {0};

typedef struct ListNode ListNode;

ListNode* modifiedList(int* nums, int n, ListNode* head) {
	for (int i = 0; i < n; i++) {
		map[nums[i] - 1] = 1;
	}

	ListNode dummyHead = { .next = head };
	ListNode* node = &dummyHead;
	ListNode* next;

	while ((next = node->next) != NULL) {
		if (map[next->val - 1]) {
			node->next = next->next;
			free(next);
		}
		else node = node->next;
	}

	for (int i = 0; i < n; i++) {
		map[nums[i] - 1] = 0;
	}

	return dummyHead.next;
}

int main(int argc, char* argv[]) {
	int nums[100], n;
	ListNode dummyHead;
	readArgs(argc, argv, "#d*d", nums, &n, &dummyHead);
	return 0;
}
