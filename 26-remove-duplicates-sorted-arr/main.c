#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int removeDuplicates(int* nums, int n) {
	int k = 1;
    for (int i = 1; i < n; i++) {
		if (nums[i] != nums[i - 1]) {
			nums[k++] = nums[i];
		}
	}
	return k;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("format: program int[]\n");
	}
	int nums[100];
	int charsRead, offset = 0, cnt = 0;
	while (1 == sscanf(argv[1] + offset, "%*c%d%n", &nums[cnt], &charsRead)) {
		cnt++;
		offset += charsRead;
	}
	printf("%d\n", cnt = removeDuplicates(nums, cnt));
	for (int i = 0; i < cnt; i++) {
		printf("%d ", nums[i]);
	} printf("\n");
	return 0;
}
