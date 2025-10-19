#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	struct ListNode* next;
};

typedef struct ListNode Node; 

Node* swapNextTwo(Node* head) {
	Node* a = head->next;
	if (a == NULL) return NULL;
	Node* b = a->next;
	if (b == NULL) return NULL;
	Node* c = b->next;
	head->next = b;
	b->next = a;
	a->next = c;
	return a;
}
 
Node* swapPairs(Node* head) {
    Node dummyHead = (Node) {.next = head};
	Node* node = &dummyHead;
	while ((node = swapNextTwo(node)) != NULL);
	return dummyHead.next;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("format: program int[]\n");
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
	node->next = NULL;
	node = swapPairs(dummyHead.next);
	while (node != NULL) {
		printf("%d ", node->val);
		node = node->next;
	} printf("\n");
}
