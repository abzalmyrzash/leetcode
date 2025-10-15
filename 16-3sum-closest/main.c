#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

int cmp (const void* a, const void* b) {
	return *(int*)a - *(int*)b;
}

int threeSumClosest(int* nums, int n, int target) {
	if (n == 3) return nums[0] + nums[1] + nums[2];
	qsort(nums, n, sizeof(int), cmp);

	int minDiff = INT_MAX;
	int closestSum;
	int i = 0;
	int x, sum, diff;
	int left, right;

	while (i < n - 2) {
		x = nums[i];
		left = (i + 1);
		right = (n - 1);

		while (left != right) {
			sum = x + nums[left] + nums[right];
			if (sum == target) return sum;
			diff = abs(sum - target);
			if (diff < minDiff) {
				minDiff = diff;
				closestSum = sum;
			}
			if (sum < target) left++; 
			else right--;
		}

		i++;
	}

	return closestSum;
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
	printf("%d\n", threeSumClosest(nums, cnt, target));
	return 0;
}
