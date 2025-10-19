#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


struct ListNode {
    int val;
    struct ListNode *next;
};

typedef struct ListNode Node;

Node* reverseNextK(Node* head, int k) {
	Node *p, *a, *b, *c;
	a = head->next;
	for (int i = 0; i < k; i++) {
		if (a == NULL) return NULL;
		a = a->next;
	}
	p = head;
	a = p->next;
	b = a->next;
	for (int i = 1; i < k; i++) {
		a->next = b->next;
		b->next = p->next;
		p->next = b;
		b = a->next;
	}
	return a;
}

Node* reverseKGroup(Node* head, int k) {
    Node dummyHead = (Node) { .next = head };
	Node* node = &dummyHead;
	while((node = reverseNextK(node, k)) != NULL);
	return dummyHead.next;
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
	node->next = NULL;
	int k;
	sscanf(argv[2], "%d", &k);
	node = reverseKGroup(dummyHead.next, k);
	while (node != NULL) {
		printf("%d ", node->val);
		node = node->next;
	} printf("\n");
}
