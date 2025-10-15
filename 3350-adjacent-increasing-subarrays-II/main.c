#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

int maxIncreasingSubarrays(int* nums, int n) {
	int map[n];
	map[0] = 1;
    for (int i = 1; i < n; i++) {
		if (nums[i] > nums[i - 1])
			map[i] = map[i - 1] + 1;
		else
			map[i] = 1;
	}
	int maxK = 1;
	int i = n - 1;
	while (i >= 0) {
		int k = map[i];
		i -= k;
		printf("%d ", k);
		if (i >= 0 && map[i] > k / 2) {
			if(map[i] < k) k = map[i];
		}
		else k = k / 2;
		printf("%d ", k);
		if (k > maxK) maxK = k;
		printf("%d\n", maxK);
	}
	return maxK;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("format: <program> <array> <k>\n");
		return 1;
	}
	int charsRead, offset = 0;
	int nums[100], cnt = 0;
	while(1 == sscanf(argv[1] + offset, "%*c%d%n", &nums[cnt], &charsRead)) {
		cnt++;
		offset += charsRead;
	}
	printf("%d\n", maxIncreasingSubarrays(nums, cnt));
	return 0;
}
