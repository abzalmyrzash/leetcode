#include "..\readargs.h"
#include <string.h>
#include <stdbool.h>

#define LEFT -1
#define RIGHT 1

bool simulate(int* nums, int n, int pos, int dir) {
	int i = pos;
	while (i >= 0 && i < n) {
		if (nums[i] == 0) i += dir;
		else if (nums[i] > 0) {
			nums[i]--;
			dir = -dir;
			i += dir;
		}
	}
	for (i = 0; i < n; i++) {
		if (nums[i] != 0) return false;
	}
	return true;
}

int countValidSelections(int* nums, int n) {
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (nums[i] == 0) {
			int copy[n];
			memcpy(copy, nums, sizeof copy);
			cnt += simulate(copy, n, i, LEFT);
			memcpy(copy, nums, sizeof copy);
			cnt += simulate(copy, n, i, RIGHT);
		}
	}
	return cnt;
}

int main(int argc, char* argv[]) {
	int nums[100], n;
	readArgs(argc, argv, "#d", nums, &n);
	printf("%d\n", countValidSelections(nums, n));
	return 0;
}
