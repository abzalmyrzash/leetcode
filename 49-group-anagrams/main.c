#include "..\readargs.h"
#include <stdlib.h>
#include <string.h>

int hash(short* freq, int hashSize) {
	int h = 0;
	int factor = 1;
	for (int i = 0; i < 26; i++) {
		h = (h + freq[i] * factor) % hashSize;
		factor = (factor * 26) % hashSize;
	}
	printf("Hash: %d\n", h);
	return h;
}

typedef struct HashNode {
	short* freq;
	char** strs;
	int size;
	int cap;
	struct HashNode *next;
} HashNode;

typedef struct {
	HashNode* arr;
	int size;
} HashMap;

HashMap* newHashMap(int size) {
	HashMap* map = malloc(sizeof(HashMap));
	map->arr = calloc(size, sizeof(HashNode));
	map->size = size;
	return map;
}

void initHashNode(HashNode* node, short* freq, char* s) {
	node->freq = freq;
	node->size = 1;
	node->cap = 1;
	node->strs = malloc(sizeof(char*) * node->cap);
	node->strs[0] = s;
	node->next = NULL;
}

void hashInsert(HashMap* hashMap, short* freq, char* s) {
	int h = hash(freq, hashMap->size);
	HashNode* node = &hashMap->arr[h];
	if (node->freq == NULL) {
		initHashNode(node, freq, s);
		return;
	}

	const int freqSize = 26 * sizeof(freq[0]);

	while (memcmp(node->freq, freq, freqSize) != 0) {
		HashNode* next = node->next;
		// add new hash node
		if (next == NULL) {
			node->next = malloc(sizeof(HashNode));
			initHashNode(node->next, freq, s);
			return;
		}
		node = next;
	}

	// same frequency, add s to corresponding strs list
	if (node->size == node->cap) {
		node->cap *= 2;
		node->strs = realloc(node->strs, node->cap * sizeof(char*));
	}
	node->strs[node->size++] = s;
}

void hashClear(HashMap* hashMap) {
	for (int i = 0; i < hashMap->size; i++) {
		HashNode* node = hashMap->arr[i].next;
		while (node != NULL) {
			HashNode* next = node->next;
			free(node);
			node = next;
		}
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int n, int* retSize, int** retColSizes) {
	char*** res = malloc(n * sizeof(char**));
	int* colSizes = malloc(n * sizeof(int));
	int size = 0;

	HashMap* map = newHashMap(n);
	short freq[n][26];
	memset(freq, 0, sizeof freq);

	for (int i = 0; i < n; i++) {
		char* s = strs[i];
		char c;
		for (int j = 0; (c = s[j]) != '\0'; j++) {
			freq[i][c - 'a']++;
		}
		hashInsert(map, freq[i], s);
	}

	for (int i = 0; i < n; i++) {
		HashNode* node = &map->arr[i];
		if (node->freq == NULL) continue;
		while (node != NULL) {
			res[size] = node->strs;
			colSizes[size] = node->size;
			size++;
			node = node->next;
		}
	}

	hashClear(map);
	free(map);

	*retSize = size;
	*retColSizes = colSizes;
	return res;
}

int main(int argc, char* argv[]) {
	char** strs;
	int n;
	readArgs(argc, argv, "#s", strs, &n);
	int size, *colSizes;
	char*** res = groupAnagrams(strs, n, &size, &colSizes);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < colSizes[i]; j++) {
			printf("%s ", res[i][j]);
		} printf("\n");
	}
	return 0;
}
