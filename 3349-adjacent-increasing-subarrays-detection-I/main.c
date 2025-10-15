#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

bool hasIncreasingSubarrays(int* nums, int n, int k) {
	int incLen[n];
	incLen[0] = 1;
    for (int i = 1; i < n; i++) {
		if (nums[i] > nums[i - 1])
			incLen[i] = incLen[i - 1] + 1;
		else
			incLen[i] = 1;
	}
	for (int i = k - 1; i < n - k; i++) {
		if (incLen[i] >= k && (incLen[i + k] == k ||
					incLen[i + k] == incLen[i] + k))
			return true;
	}
	return false;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("format: <program> <array> <k>\n");
		return 1;
	}
	int charsRead, offset = 0;
	int nums[100], cnt = 0;
	while(1 == sscanf(argv[1] + offset, "%*c%d%n", &nums[cnt], &charsRead)) {
		cnt++;
		offset += charsRead;
	}
	int k;
	sscanf(argv[2], "%d", &k);
	printf("%d\n", hasIncreasingSubarrays(nums, cnt, k));
	return 0;
}
