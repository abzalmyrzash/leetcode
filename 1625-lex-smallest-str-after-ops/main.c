#define _CRT_SECURE_NO_WARNINGS
#include "../readargs.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

char* add(char* s, int len, int a) {
	char* t = malloc(len + 1);
	for (int i = 0; i < len; i += 2) {
		t[i] = s[i];
	}
	for (int i = 1; i < len; i += 2) {
		t[i] = s[i] + a;
		if (t[i] > '9') t[i] -= 10;
	}
	t[len] = '\0';
	return t;
}

char* rotate(char* s, int len, int b) {
	char* t = malloc(len + 1);
	for (int i = b; i < len; i++) {
		t[i] = s[i - b];
	}
	for (int i = 0; i < b; i++) {
		t[i] = s[len - b + i];
	}
	t[len] = '\0';
	return t;
}

#define HASH_SIZE 10000

int hash(char* s) {
	int h = 0;
	while (*s != '\0') {
		h = (10 * h + (*s - '0')) % HASH_SIZE;
		s++;
	}
	return h;
}

struct HashNode {
	char* str;
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

bool hashInsert(char* s) {
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
	node->next = NULL;
	return true;
}

bool hashFind(char* s) {
	struct HashNode* node = hashMap[hashFunction(s)];
	if (node == NULL) return false;
	// search until string is found
	while (strcmp(node->str, s)) {
		node = node->next;
		if (node == NULL) return false;
	}
	return true;
}

void hashClear() {
	for (int i = 0; i < HASH_SIZE; i++) {
		if (hashMap[i] != NULL) {
			struct HashNode* node = hashMap[i];
			struct HashNode* next;
			while (node != NULL) {
				free(node->str);
				next = node->next;
				free(node);
				node = next;
			}
			hashMap[i] = NULL;
		}
	}
}

#define QCAP 10000
char* queue[QCAP];
int qSize, qStart, qEnd;

void initQ() {
	qSize = 0; qStart = 0; qEnd = 0;
}

void pushQ(char* s) {
	queue[qEnd] = s;
	qSize++; qEnd++;
	if (qEnd == QCAP) qEnd = 0;
}

char* popQ() {
	char* s = queue[qStart];
	qSize--;
	qStart++;
	if (qStart == QCAP) qStart = 0;
	return s;
}

char* findLexSmallestString(char* s, int a, int b) {
	char* min = s;
	int len = strlen(s);
	char* s0, *s1, *s2;
	s0 = malloc(len + 1);
	strcpy(s0, s);
	initQ();
	pushQ(s0);
	hashInit();
	hashInsert(s0);

	while(qSize) {
		s0 = popQ();
		s1 = add(s0, len, a);
		s2 = rotate(s0, len, b);
		/* printf("%s ==> %s, %s\n", s0, s1, s2); */
		if (hashInsert(s1)) {
			/* printf("%s inserted\n", s1); */
			pushQ(s1);
			if (-1 == strcmp(s1, min)) min = s1;
		}
		if (hashInsert(s2)) {
			/* printf("%s inserted\n", s2); */
			pushQ(s2);
			if (-1 == strcmp(s2, min)) min = s2;
		}
		/* printf("%d %d %d\n\n", qSize, qStart, qEnd); */
	}
	char* minCopy = malloc(len + 1);
	strcpy(minCopy, min);
	hashClear();
	return minCopy;
}

int main(int argc, char* argv[]) {
	char* s;
	int a, b;
	readArgs(argc, argv, "sdd", &s, &a, &b);
	printf("%s\n", findLexSmallestString(s, a, b));
	return 0;
}
