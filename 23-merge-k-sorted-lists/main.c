#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct ListNode {
     int val;
     struct ListNode *next;
 };

typedef struct ListNode ListNode;

#define MAX_SIZE 500 * 10000
typedef struct {
	ListNode* data[MAX_SIZE];
	int size;
} Heap;

void heapInit(Heap* heap) {
	heap->size = 0;
}

#define SWAP(TYPE, A, B) TYPE tmp = A; A = B; B = tmp;

void heapInsert(Heap* heap, ListNode* node) {
	ListNode** arr = heap->data;
	int i = heap->size;
	arr[heap->size++] = node;
	// sift up
	while (1) {
		int parent = (i - 1) / 2;
		if(arr[i]->val < arr[parent]->val) {
			SWAP(ListNode*, arr[i], arr[parent]);
			if (parent == 0) break;
			i = parent;
		} else break;
	}
}

ListNode* heapExtract(Heap* heap) {
	if (heap->size == 0) return NULL;
	ListNode** arr = heap->data;
	ListNode* min = arr[0];
	arr[0] = arr[--heap->size];
	int i = 0;
	// sift down
	int size = heap->size;
	while (1) {
		int child1 = 2 * i + 1;
		int child2 = 2 * i + 2;
		int smallest = i;

		if (child1 < size && arr[child1]->val < arr[smallest]->val) {
			smallest = child1;
		}
		if (child2 < size && arr[child2]->val < arr[smallest]->val){
			smallest = child2;
		}

		if (smallest != i) {
			SWAP(ListNode*, arr[i], arr[smallest]);
			i = smallest;
		} else break;
	}
	return min;
}
 
ListNode* mergeKLists(ListNode** lists, int listsSize) {
	static Heap heap;
	heapInit(&heap);

    ListNode dummyHead = { .val = INT_MIN, .next = NULL };
	for (int i = 0; i < listsSize; i++) {
		while (lists[i] != NULL) {
			heapInsert(&heap, lists[i]);
			lists[i] = lists[i]->next;
		}
	}

    ListNode* node = &dummyHead;
	while(node != NULL) {
		node->next = heapExtract(&heap);
		node = node->next;
	}

	return dummyHead.next;
}

int main(int argc, char** argv) {
	if (argc == 1) return 1;
	struct ListNode* lists[argc-1];
	for (int i = 1; i < argc; i++) {
		struct ListNode* list = malloc(sizeof(struct ListNode));
		int readCharCnt, offset = 0;
		if (1 > sscanf(argv[i], "%d%n", &list->val, &readCharCnt)) {
			free(list);
			lists[i - 1] = NULL;
			continue;
		}
		list->next = NULL;
		lists[i - 1] = list;
		struct ListNode* node = list;
		while (1) {
			node->next = malloc(sizeof(struct ListNode));
			offset += readCharCnt;
			if (1 > sscanf(argv[i] + offset, "%d%n", &node->next->val, &readCharCnt)) {
				free(node->next);
				node->next = NULL;
				break;
			}
			node = node->next;
		}
	}

	for (int i = 0; i < argc - 1; i++) {
		struct ListNode* list = lists[i];
		while (list != NULL) {
			printf("%d ", list->val);
			list = list->next;
		}
		printf("\n");
	}

	struct ListNode* merged = mergeKLists(lists, argc - 1);
	while (merged != NULL) {
		printf("%d ", merged->val);
		merged = merged->next;
	}

	return 0;
}
