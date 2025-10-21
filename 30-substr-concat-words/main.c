#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void kmpTable(char* s, int len, int* T) {
	T[0] = -1;
	int i = 1, j = 0;

	while (i < len) {
		if (s[i] == s[j]) T[i] = T[j];
		else {
			T[i] = j;
			while (j >= 0 && s[i] != s[j]) {
				j = T[j];
			}
		}
		i++; j++;
	}
	T[len] = j;
}

typedef struct {
	int size;
	int cap;
	int* data;
	int* og_data;
} Array;

void array_push(Array* arr, int elem) {
	if (arr->size >= arr->cap) {
		if (arr->cap == 0) arr->cap = 2;
		else arr->cap *= 2;
		arr->data = realloc(arr->data, arr->cap * sizeof(int));
	}
	arr->data[arr->size++] = elem;
}

Array findAll(char* hay, int hayLen, char* n, int nLen) {
	Array arr = { 0 };
	int T[nLen + 1];
	kmpTable(n, nLen, T);
	int i = 0, j = 0;
	int cnt = 0;

	while (i < hayLen) {
		if (hay[i] == n[j]) {
			i++; j++;
			if (j == nLen) {
				array_push(&arr, i - j);
			}
		} else {
			j = T[j];
			if (j < 0) {
				i++; j++;
			}
		}
	}
	return arr;
}

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
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
// array of dynamic arrays of indices at which each word occurs
	Array F[n];
	memset(F, 0, sizeof F);
	int* f[n]; // shifted pointers to arrays in F
	int fc[n]; // number of occurrences left
// array of count for each word in words list
// (at the index where it is first in words list)
	int C[n];
	memset(C, 0, sizeof C);
	hashInit();

	for (int i = 0; i < n; i++) {
		struct HashNode* node = hashFind(words[i]);
		// if meeting word for the first time
		if (node == NULL) { 
			// insert word with its index in hash map
			hashInsert(words[i], i);
			// find all occurrences of the word in s
			F[i] = findAll(s, sLen, words[i], wLen);
			f[i] = F[i].data;
			fc[i] = F[i].size;
			C[i] = 1;
			// if none was found goto ret where it returns an empty array
			if (F[i].size == 0) {
				goto ret;
			}
		} else {
			//printf("hash found\n");
		// we don't store occurrences for repeating words
			fc[i] = F[i].size = 0;
			f[i] = F[i].data = NULL;
			C[node->val]++; // but increment counter at the original index
		// if there are less occurrences of word in s than there are in words list
			if (F[node->val].size < C[node->val]) {
				// also return an empty array
				goto ret;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		//printf("%d\n", C[i]);
		//for (int j = 0; j < F[i].size; j++) {
			//printf("%d ", F[i].data[j]);
		//} printf("\n");
	}

// required length for a concatenated string
	int reqLen = n * wLen;

	while (1) {
	// start of s where it could be a valid concatenated string,
	// or in other terms minimum index at which a word occurs
		int start = sLen;
		int w; // index of a word that occurs first
	// loop through words, find the word that occurs first
		for (int i = 0; i < n; i++) {
			if (C[i] == 0) continue;
			if (f[i][0] < start) {
				start = f[i][0];
				w = i;
			} 
		}
		//printf("%s %d\n", words[w], start);

	// now we check if s + start really is a concatenation of words
	// loop through words
		for (int i = 0; i < n; i++) {
			if (C[i] == 0) continue;
			int cnt = 0; // how many occurrences fit concatenation
			int j = 0; // index in f[i]
		// loop where we check each occurrence of the word
			while (1) {
				// position relative to start of concatenated string
				int pos = f[i][j] - start;
				//printf("%s %d\n", words[i], pos);
				// if pos is out of range, s + start is not valid concat
				if (pos >= reqLen) goto isNotConcat;
				// if pos divides by word length,
				// pos is valid and we increment cnt
				if (pos % wLen == 0) {
					cnt++;
					// if we find required number of occurences
					if (cnt == C[i]) break;
				}
				// go to next occurrence, until no more left
				if (++j == fc[i]) goto isNotConcat;
			}
		}

	// start is valid if loop reached end without goto isNotConcat
		//printf("%d\n", start);
		array_push(&res, start);

		isNotConcat:

	// shift pointer to array of occurrences for w
	// so we don't search from the same start position again
		f[w]++;
		fc[w]--;
	// when no more occurrences, break
		if (fc[w] == 0)
			break; 
		//printf("\n");
	}

	ret:
	//printf("ret\n");
	//fflush(stdout);
	// free memory
	hashClear();
	//printf("hash cleared\n");
	//fflush(stdout);
	for (int i = 0; i < n; i++) {
		if (F[i].data != NULL) {
			free(F[i].data);
		}
	}
	//printf("F cleared\n");
	//fflush(stdout);

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
