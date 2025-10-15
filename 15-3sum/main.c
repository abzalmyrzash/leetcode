#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define MAX_SIZE 200001
#define MIN -100000
int map[MAX_SIZE];
bool iMap[MAX_SIZE];
bool jMap[MAX_SIZE];

int twoSum(int* nums, int size, int i, int** arr) {
	int sum = -nums[i];
	for (int j = i+1; j < size; j++) {
		map[nums[j]-MIN] = INT_MIN;
		jMap[nums[j]-MIN] = false;
	}
	for (int j = i+1; j < size; j++) {
		int index = (sum - nums[j]) - MIN;
		if (index >= 0 && index < MAX_SIZE &&
				map[(sum-nums[j])-MIN] == INT_MIN) {
			map[(sum-nums[j])-MIN] = j;
		}
	}
	int cnt = 0;
	for (int j = i+1; j < size; j++) {
		int nj = nums[j];
		int k = map[nums[j]-MIN];
		if (k == INT_MIN) continue;
		if (j == k) continue;
		int nk = nums[k];
		if (jMap[nj-MIN]) continue;
		if (jMap[nk-MIN]) continue;
		arr[cnt][1] = nj;
		arr[cnt][2] = nk;
		jMap[nj-MIN] = true;
		jMap[nk-MIN] = true;
		cnt++;
	}
	return cnt;
}

int cmp (const void* a, const void* b) {
	int A = *(int*)a;
	int B = *(int*)b;
	if (A < B) return -1;
	if (A > B) return 1;
	return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
	qsort(nums, numsSize, sizeof(int), cmp);

	int arrSize = numsSize * 10;
	int** arr = malloc(arrSize*sizeof(int*));
	for (int i = 0; i < arrSize; i++) {
		arr[i] = malloc(3*sizeof(int));
	}

	for (int i = 0; i < numsSize; i++) {
		iMap[nums[i]-MIN] = false;
		jMap[nums[i]-MIN] = false;
		map[nums[i]-MIN] = INT_MIN;
	}

	int offset = 0;
	for (int i = 0; i < numsSize - 2; i++) {
		int ni = nums[i];
		if (!iMap[ni-MIN]) {
			int size = twoSum(nums, numsSize, i, arr+offset);
			for (int j = 0; j < size; j++) {
				arr[j+offset][0] = ni;
			}
			offset += size;
			iMap[ni-MIN] = true;
		}
	}

	*returnSize = offset;
    *returnColumnSizes = malloc(*returnSize * sizeof(int));
	for (int i = 0; i < *returnSize; i++) {
		(*returnColumnSizes)[i] = 3;
	}
	return arr;
}

int main(int argc, char* argv[]) {
	if (argc==1) return 1;
	int nums[argc-1];
	for (int i = 1; i < argc; i++){
		sscanf(argv[i], "%d", &nums[i-1]);
	}
	int returnSize, *returnColumnSizes;
	int** res = threeSum(nums, argc-1, &returnSize, &returnColumnSizes);
	for (int i = 0; i < returnSize; i++) {
		for (int j = 0; j < 3; j++) {
			printf("%d ", res[i][j]);
		}
		printf("\n");
	}
	return 0;
}
