#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"
#include <stdlib.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int n, int target, int* retSize) {
	int* res = malloc(2 * sizeof(int));
	*retSize = 2;
	if (n == 0) {
		res[0] = -1;
		res[1] = -1;
		return res;
	}

	int low = 0;
	int high = n - 1;
	int i;

	while (low <= high)  {
		i = low + (high - low) / 2;
		if (nums[i] == target) break;
		if (target < nums[i]) {
			high = i - 1;
		}
		else {
			low = i + 1;
		}
	}

	if (low > high) {
		res[0] = -1;
		res[1] = -1;
		return res;
	}

	printf("%d\n", i);
	int highBound = high;

	while (low <= high) {
		i = low + (high - low) / 2;
		if (nums[i] == target) {
			if (i == 0) break;
			if (nums[i - 1] < target) break;
			else {
				high = i - 1;
			}
		}
		else if (nums[i] < target) {
			low = i + 1;
		}
		else {
			printf("does this happen?\n");
			high = i - 1;
			highBound = high;
		}
	}

	res[0] = i;
	printf("%d\n", i);
	low = i;
	high = highBound;

	while (low <= high) {
		i = low + (high - low) / 2;
		if (nums[i] == target) {
			if (i == n - 1) break;
			if (nums[i + 1] > target) break;
			else {
				low = i + 1;
			}
		}
		else if (nums[i] > target) {
			high = i - 1;
		}
		else {
			printf("does this happen too?\n");
			low = i + 1;
		}
	}

	res[1] = i;
	printf("%d\n", i);

	return res;
}

int main(int argc, char* argv[]) {
	int nums[100], n, target;
	readArgs(argc, argv, "#dd", nums, &n, &target);
	int size;
	int* res = searchRange(nums, n, target, &size);
	printf("%d %d\n", res[0], res[1]);
	return 0;
}
