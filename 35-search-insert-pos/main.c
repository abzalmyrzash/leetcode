#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"

int searchInsert(int* nums, int n, int target) {
    int low = 0;
	int high = n - 1;
	int i;
	while (low <= high) {
		i = low + (high - low) / 2;
		if (nums[i] == target) {
			break;
		}
		if (target < nums[i]) {
			if (i == 0) break;
			if (nums[i - 1] < target) break;
			high = i - 1;
		}
		else {
			if (i == n - 1) {
				i++;
				break;
			}
			if (nums[i + 1] > target) {
				i++;
				break;
			}
			low = i + 1;
		}
	}
	return i;
}

int main(int argc, char* argv[]) {
	int nums[100], n, target;
	readArgs(argc, argv, "#dd", nums, &n, &target);
	printf("%d\n", searchInsert(nums, n, target));
	return 0;
}
