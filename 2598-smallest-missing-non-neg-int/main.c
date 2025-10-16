#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <limits.h>

int findSmallestInteger(int* nums, int n, int value) {
	int map[value]; // map of how many times remainders occur
	memset(map, 0, sizeof map);
    for (int i = 0; i < n; i++) {
		int rem = nums[i] % value;
		if (rem < 0) rem += value;
		map[rem]++;
	}
	int minCnt = INT_MAX;
	int rarestRem;
	for (int i = 0; i < value; i++) {
		if (map[i] < minCnt) {
			minCnt = map[i];
			rarestRem = i;
		}
	}
	return rarestRem + value * minCnt;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("format: program int[] int\n");
	}
	int nums[100];
	int charsRead, offset = 0, cnt = 0;
	while (1 == sscanf(argv[1] + offset, "%*c%d%n", &nums[cnt], &charsRead)) {
		cnt++;
		offset += charsRead;
	}
	int value;
	sscanf(argv[2], "%d", &value);
	printf("%d\n", findSmallestInteger(nums, cnt, value));
}
