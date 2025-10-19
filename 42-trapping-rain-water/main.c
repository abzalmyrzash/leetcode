#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int trap(int* h, int n) {
	int max = 0;
	for (int i = 1; i < n; i++) {
		if (h[i] > h[max]) max = i;
	}
	int total = 0;
	int lMax = 0;
	for (int i = 0; i < max; i++) {
		if (h[i] > h[lMax]) lMax = i;
		total += h[lMax] - h[i];
	}
	int rMax = n - 1;
	for (int i = n - 2; i > max; i--) {
		if (h[i] > h[rMax]) rMax = i;
		total += h[rMax] - h[i];
	}
	return total;
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("format: program int[]\n");
		return 1;
	}
	int nums[100];
	int charsRead, offset = 0, cnt = 0;
	while(1 == sscanf(argv[1] + offset, "%*c%d%n", &nums[cnt], &charsRead)) {
		cnt++;
		offset += charsRead;
	}
	printf("%d\n", trap(nums, cnt));
	return 0;
}
