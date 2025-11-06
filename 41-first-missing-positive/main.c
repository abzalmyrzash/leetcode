#include "..\readargs.h"
#include <limits.h>
#include <stdbool.h>
#include <string.h>

int firstMissingPositive(int* nums, int n) {
	bool arr[n];
	memset(arr, 0, sizeof arr);
	for (int i = 0; i < n; i++) {
		int num = nums[i];
		if (num <= 0) continue;
		if (num <= n) {
			arr[num - 1] = true;
		}
	}
	for (int i = 0; i < n; i++) {
		if (!arr[i]) return i + 1;
	}
	return n + 1;
}

int main(int argc, char* argv[]) {
	int nums[100], n;
	readArgs(argc, argv, "#d", nums, &n);
	printf("%d\n", firstMissingPositive(nums, n));
	return 0;
}
