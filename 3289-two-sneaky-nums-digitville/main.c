#include "..\readargs.h"
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* getSneakyNumbers(int* nums, int n, int* returnSize) {
    *returnSize = 2;
	int* res = malloc(2 * sizeof(int));
	_Bool seen[n];
	memset(seen, 0, sizeof seen);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int num = nums[i];
		if (!seen[num]) {
			seen[num] = 1;
		} else {
			res[cnt++] = num;
		}
	}
	return res;
}

int main(int argc, char* argv[]) {
	int nums[100], n;
	readArgs(argc, argv, "#d", nums, &n);
	int size;
	int* res = getSneakyNumbers(nums, n, &size);
	for (int i = 0; i < size; i++) {
		printf("%d ", res[i]);
	} printf("\n");
	return 0;
}
