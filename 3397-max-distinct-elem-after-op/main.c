#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"
#include <stdlib.h>

int cmp(const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int maxDistinctElements(int* nums, int n, int k) {
	qsort(nums, n, sizeof(int), cmp);
	int res = 1;
	nums[0] -= k;
	for (int i = 1; i < n; i++) {
		int diff = nums[i] - (nums[i - 1] + 1);
		if (diff < -k) diff = -k;
		else res++;
		if (diff > k) diff = k;
		nums[i] -= diff;
	}
    return res;
}

int main(int argc, char* argv[]) {
	int nums[100], size, k;
	readArgs(argc, argv, "#dd", nums, &size, &k);
	printf("%d\n", maxDistinctElements(nums, size, k));
	return 0;
}
