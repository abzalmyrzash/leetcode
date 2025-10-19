#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int removeElement(int* nums, int n, int val) {
	int k = 0;
    for (int i = 0; i < n; i++) {
		if (nums[i] != val) {
			nums[k++] = nums[i];
		}
	}
	return k;
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
	int val;
	sscanf(argv[2], "%d", &val);
	printf("%d\n", cnt = removeElement(nums, cnt, val));
	for (int i = 0; i < cnt; i++) {
		printf("%d ", nums[i]);
	} printf("\n");
	return 0;
}
