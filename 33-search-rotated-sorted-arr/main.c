#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"

int search(int* nums, int n, int target) {
	int low = 0;
	int high = n - 1;
	int k = 0;
	while (low <= high) {
		int i = low + (high - low) / 2;
		if (nums[low] > nums[i]) {
			if (nums[i - 1] > nums[i]) {
				k = i;
				break;
			}
			high = i - 1;
		}
		else if (nums[high] < nums[i]) {
			if (nums[i + 1] < nums[i]) {
				k = i + 1;
				break;
			}
			low = i + 1;
		}
		else break;
	}
	printf("k = %d\n", k);
	low = k;
	high = n + k - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		int i = mid % n;
		if (nums[i] == target) return i;
		if (nums[i] > target) {
			high = mid - 1;
		} else {
			low = mid + 1;
		}
	}
	return -1;
}

int main(int argc, char* argv[]) {
	int nums[100], n, target;
	readArgs(argc, argv, "#dd", nums, &n, &target);
	printf("%d\n", search(nums, n, target));
	return 0;
}
