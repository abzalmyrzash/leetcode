#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

typedef struct ListNode Node; 

Node* removeNthFromEnd(Node* head, int n) {
	Node* node = head;
	Node* remove = head;
	Node dummyHead = (Node){ .next = head };
	Node* parent = &dummyHead;
    while (n--) {
		node = node->next;
	}
	while(node != NULL) {
		node = node->next;
		remove = remove->next;
		parent = parent->next;
	}
	if (head == remove) head = head->next;
	parent->next = remove->next;
	free(remove);
	return head;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("format: program int[] int\n");
		return 1;
	}
	int num;
	Node dummyHead = (Node) { .next = NULL };
	Node* node = &dummyHead;
	int charsRead, offset = 0;
	while (1 == sscanf(argv[1] + offset, "%*c%d%n", &num, &charsRead)) {
		node->next = malloc(sizeof(Node));
		node = node->next;
		node->val = num;
		offset += charsRead;
	}
	int n;
	sscanf(argv[2], "%d", &n);
	node = removeNthFromEnd(dummyHead.next, n);
	while (node != NULL) {
		printf("%d ", node->val);
		node = node->next;
	} printf("\n");
}
