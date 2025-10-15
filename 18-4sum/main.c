#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

int cmp (const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int n, int target, int* returnSize, int** returnColumnSizes) {
	int capacity = 256;
	int** res = malloc(capacity * sizeof(int*));
	int cnt = 0;
	qsort(nums, n, sizeof(int), cmp);
	int x, y;
	long long sum2, sum4;
	int *left, *right;
	for (int i = 0; i < n - 3; i++) {
		x = nums[i];
        if (i > 0 && x == nums[i - 1]) continue; // skip duplicates
		for (int j = i + 1; j < n - 2; j++) {
			y = nums[j];
        	if (j > i + 1 && y == nums[j - 1]) continue; // skip duplicates
			sum2 = x + y;
			if (sum2 + nums[j+1] + nums[j+2] > target) break; // too large
			if (sum2 + nums[n-1] + nums[n-2] < target) continue; // too small
			left = nums + (j + 1);
			right = nums + (n - 1);
			while (left < right) {
				int leftVal = *left;
				int rightVal = *right;
				sum4 = sum2 + leftVal + rightVal;
				if (sum4 == target) {
					int* quint = malloc(sizeof(int)*4);
					quint[0] = x;
					quint[1] = y;
					quint[2] = leftVal;
					quint[3] = rightVal;
					//printf("%d %d %d %d\n", x, y, leftVal, rightVal);
					if (cnt == capacity) {
						capacity *= 2;
						res = realloc(res, capacity * sizeof(int*));
					}
					res[cnt++] = quint;
				nextValues:
					do {
						left++;
					} while (left < right && *left == leftVal);
					do {
						right--;
					} while (left < right && *left == leftVal);
				}
				else if (sum4 < target) left++;
				else right--;
			}
		}
	}
	*returnSize = cnt;
	*returnColumnSizes = malloc(cnt * sizeof(int));
	for (int i = 0; i < cnt; i++) {
		(*returnColumnSizes)[i] = 4;
	}
	return res;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("format: <program> <array> <target>\n");
		return 1;
	}
	int charsRead, offset = 0;
	int nums[100], cnt = 0;
	while(1 == sscanf(argv[1] + offset, "%*c%d%n", &nums[cnt], &charsRead)) {
		cnt++;
		offset += charsRead;
	}
	int target;
	sscanf(argv[2], "%d", &target);
	int returnSize, *returnColumnSizes;
	int** res = fourSum(nums, cnt, target, &returnSize, &returnColumnSizes);
	printf("%d\n", returnSize);
	for (int i = 0; i < returnSize; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%d ", res[i][j]);
		}
		printf("\n");
	}
	return 0;
}
