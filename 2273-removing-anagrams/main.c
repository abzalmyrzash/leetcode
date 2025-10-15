#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** removeAnagrams(char** words, int wordsSize, int* returnSize) {
	bool removed[wordsSize];
	int removedCnt = 0;
	memset(removed, 0, sizeof removed);
	int map[wordsSize][26];
	memset(map, 0, sizeof map);

	for (int i = 0; i < wordsSize; i++) {
		if (removed[i]) continue;
		char* w = words[i];
		int len = strlen(w);
		for (int j = 0; j < len; j++) {
			char c = w[j] - 'a';
			map[i][c]++;
		}
	}

	for(int i = 0; i < wordsSize-1; i++) {
		char* w = words[i];
		int len = strlen(w);
		char* w2 = words[i+1];
		int len2 = strlen(w2);
		if (len != len2) continue;
		bool isAnagram = true;
		for (int k = 0; k < len; k++) {
			char c = w[k] - 'a';
			if (map[i][c] != map[i+1][c]) {
				isAnagram = false;
				break;
			}
		}
		if (isAnagram) {
			removed[i+1] = true;
			removedCnt++;
		}
	}

	*returnSize = wordsSize - removedCnt;
    char** res = malloc(*returnSize*sizeof(char*));
	int cnt = 0;
	for (int i = 0; i < wordsSize; i++) {
		if (!removed[i]) res[cnt++] = words[i];
	}
	return res;
}

int main(int argc, char* argv[]) {
	int returnSize;
	char** words = removeAnagrams(argv+1, argc-1, &returnSize);
	for (int i = 0; i < returnSize; i++) {
		printf("%s ", words[i]);
	}
	free(words);
	return 0;
}
