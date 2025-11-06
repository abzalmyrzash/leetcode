#include "..\readargs.h"
#include <math.h>

int jump(int* nums, int n) {
    int jumps = 0, end = 0, reach = 0;
    for (int i = 0; i < n - 1; i++) {
        reach = fmax(reach, i + nums[i]);
        if (i == end) {
            jumps++;
            end = reach;
        }
    }
    return jumps;
}

int main(int argc, char* argv[]) {
	int nums[100], n;
	readArgs(argc, argv, "#d", nums, &n);
	printf("%d\n", jump(nums, n));
	return 0;
}
