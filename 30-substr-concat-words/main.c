#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	int size;
	int cap;
	int* data;
} Array;

void array_push(Array* arr, int elem) {
	if (arr->size >= arr->cap) {
		if (arr->cap == 0) arr->cap = 2;
		else arr->cap *= 2;
		arr->data = realloc(arr->data, arr->cap * sizeof(int));
	}
	arr->data[arr->size++] = elem;
}

#define HASH_SIZE 5000

int hash(char* s) {
	int h = 0;
	while (*s != '\0') {
		h = (31 * h + *s) % HASH_SIZE;
		s++;
	}
	return h;
}

struct HashNode {
	char* str;
	int val;
	struct HashNode* next;
};

struct HashNode* hashMap[HASH_SIZE];
int (*hashFunction)(char*) = hash;
bool hashIsInit = false;

void hashInit() {
	if (hashIsInit) return;
	for (int i = 0; i < HASH_SIZE; i++) {
		hashMap[i] = NULL;
	}
	hashIsInit = true;
}

bool hashInsert(char* s, int val) {
	int hashVal = hashFunction(s);
	struct HashNode* node = hashMap[hashVal];
	/* printf("%s = %d\n", s, hash(s) % HASH_SIZE); */

	if (node == NULL) {
		hashMap[hashVal] = node = malloc(sizeof(struct HashNode));
	} else {
		do {
			// if same string is found, don't insert and return false
			if (!strcmp(s, node->str)) return false;
		} while (node->next != NULL && (node = node->next));
		node->next = malloc(sizeof(struct HashNode));
		node = node->next;
	}

	node->str = s;
	node->val = val;
	node->next = NULL;
	return true;
}

struct HashNode* hashFind(char* s) {
	struct HashNode* node = hashMap[hashFunction(s)];
	if (node == NULL) return NULL;
	// search until string is found
	while (strcmp(node->str, s)) {
		node = node->next;
		if (node == NULL) return NULL;
	}
	return node;
}

void hashClear() {
	for (int i = 0; i < HASH_SIZE; i++) {
		if (hashMap[i] != NULL) {
			struct HashNode* node = hashMap[i];
			struct HashNode* next;
			while (node != NULL) {
				next = node->next;
				free(node);
				node = next;
			}
			hashMap[i] = NULL;
		}
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int n, int* returnSize) {
    Array res = { 0 };
	int sLen = strlen(s);
	int wLen = strlen(words[0]);
// required length for a concatenated string
	int reqLen = n * wLen;

	if (sLen < reqLen) {
		*returnSize = 0;
		return malloc(sizeof(int));
	}
// array of count for each word in words list
// (at the index where it is first in words list)
	int C[n];
	memset(C, 0, sizeof C);
	hashInit();

	for (int i = 0; i < n; i++) {
		struct HashNode* node = hashFind(words[i]);
		if (node == NULL) {
			hashInsert(words[i], i);
			C[i] = 1;
		} else {
			C[node->val]++;
		}
	}

	for (int i = 0; i < wLen; i++) {
		int left = i;
		int cnt = 0;
		int window[n];
		memset(window, 0, sizeof window);
		for (int j = i; j + wLen <= sLen; j += wLen) {
			char tmp = s[j + wLen];
			s[j + wLen] = '\0';
			struct HashNode* node = hashFind(s + j);
			s[j + wLen] = tmp;
			if (node != NULL) {
				window[node->val]++;
				cnt++;
				struct HashNode* node2;
				while (window[node->val] > C[node->val]) {
					tmp = s[left + wLen];
					s[left + wLen] = '\0';
					node2 = hashFind(s + left);
					s[left + wLen] = tmp;
					if (node2 != NULL) window[node2->val]--;
					cnt--;
					left += wLen;
				}
				if(cnt == n) {
					array_push(&res, left);
					tmp = s[left + wLen];
					s[left + wLen] = '\0';
					node2 = hashFind(s + left);
					s[left + wLen] = tmp;
					if (node2 != NULL) window[node2->val]--;
					cnt--;
					left += wLen;
				}
			} else {
				memset(window, 0, sizeof window);
				cnt = 0;
				left = j + wLen;
			}
		}
	}

	hashClear();

	*returnSize = res.size;
	// malloc because leetcode can't handle NULL
	if (res.size == 0) res.data = malloc(sizeof(int));
	return res.data;
}

int main(int argc, char* argv[]) {
	char* s;
	char** words;
	int n;
	readArgs(argc, argv, "s#s", &s, words, &n);
	printf("%s\n", s);
	printf("%d\n" , n);
	for (int i = 0; i < n; i++) {
		printf("%s ", words[i]);
	} printf("\n");
	int *arr, size;
	arr = findSubstring(s, words, n, &size);
	printf("%d\n", size);
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	} printf("\n");
	return 0;
}
