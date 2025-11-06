#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"
#include <stdbool.h>

#define swap(a, b) int tmp = a; a = b; b = tmp;

bool nextPermutation(int* nums, int n) {
	if (n < 2) return false;
	if (n == 2) {
		swap(nums[0], nums[1]);
		return nums[0] <= nums[1];
	}
	bool lastPerm = true;
	for (int i = 1; i < n; i++) {
		if (nums[i] > nums[i - 1]) {
			lastPerm = false;
			break;
		}
	}
	if (lastPerm) {
		for (int i = 0; i < n / 2; i++) {
			swap(nums[i], nums[n - i - 1]);
		}
		return true;
	}
	bool reversed = nextPermutation(nums + 1, n - 1);
	if (reversed) {
		int i = 1;
		while (nums[0] >= nums[i]) {
			i++;
		}
		swap(nums[i], nums[0]);
	}
	return false;
}

int factorial(int n) {
	int res = 1;
	for (int i = 2; i <= n; i++) {
		res *= i;
	}
	return res;
}

int main(int argc, char* argv[]) {
	int nums[100], n;
	readArgs(argc, argv, "#d", nums, &n);
	int perms = factorial(n);
	for (int i = 0; i < perms; i++) {
		nextPermutation(nums, n);
		for (int j = 0; j < n; j++) {
			printf("%d ", nums[j]);
		} printf("\n");
	}
	return 0;
}
