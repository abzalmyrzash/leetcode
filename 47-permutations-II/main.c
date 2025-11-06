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
int** permuteUnique(int* nums, int n, int* retSize, int** retColSizes) {
	int size = 1;
	int cap = 1;
	int** res = malloc(cap * sizeof(int*));
	const int sizeOfNums = n * sizeof(int);
	int* copy = malloc(sizeOfNums);
	memcpy(copy, nums, sizeOfNums);
	res[0] = copy;

    while (1) {
		nextPermutation(nums, n);
		if (memcmp(nums, res[0], sizeOfNums) == 0) break;
		if (size == cap) {
			cap *= 2;
			res = realloc(res, cap * sizeof(int*));
		}
		copy = malloc(sizeOfNums);
		memcpy(copy, nums, sizeOfNums);
		res[size++] = copy;
	}

	int* colSizes = malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		colSizes[i] = n;
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
