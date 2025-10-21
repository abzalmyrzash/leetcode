#define _CRT_SECURE_NO_WARNINGS
#include "..\readargs.h"

// unsolved

int maxFrequency(int* nums, int n, int k, int m) {
}
 
int main(int argc, char* argv[]) {
	int nums[100];
	int n, k, m;
	readArgs(argc, argv, "#ddd", nums, &n, &k, &m);
	printf("%d\n", maxFrequency(nums, n, k, m));
	return 0;
}
