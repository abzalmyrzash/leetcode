#include "..\readargs.h"
#include <stdlib.h>
#include <string.h>

void swap(int* nums, int i, int j) {
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}
void reverse(int* nums, int start, int numsSize) {
    int i = start, j = numsSize - 1;
    while (i < j) {
        swap(nums, i, j);
        i++;
        j--;
    }
}
void nextPermutation(int* nums, int numsSize) {
    int i = numsSize - 2;
    while (i >= 0 && nums[i + 1] <= nums[i]) {
        i--;
    }
    if (i >= 0) {
        int j = numsSize - 1;
        while (nums[j] <= nums[i]) {
            j--;
        }
        swap(nums, i, j);
    }
    reverse(nums, i + 1, numsSize);
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int n, int* retSize, int** retColSizes) {
	int size = 1;
	for (int i = 2; i <= n; i++) {
		size *= i;
	}
	int** res = malloc(size * sizeof(int*));
	int* colSizes = malloc(size * sizeof(int));
	const int sizeOfNums = n * sizeof(int);

    for (int i = 0; i < size; i++) {
		colSizes[i] = n;
		nextPermutation(nums, n);
		int* copy = malloc(sizeOfNums);
		memcpy(copy, nums, sizeOfNums);
		res[i] = copy;
	}

	for (int i = 0; i < size; i++) {
	}
	*retSize = size;
	*retColSizes = colSizes;
	return res;
}

int main(int argc, char* argv[]) {
	int nums[100], n;
	readArgs(argc, argv, "#d", nums, &n);
	return 0;
}
