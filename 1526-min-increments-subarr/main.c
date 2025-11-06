#include "..\readargs.h"
#include <limits.h>

int minNumberOperations(int* target, int targetSize) {
    int ops = target[0];            
    for (int i = 1; i < targetSize; i++) {
        if (target[i] > target[i - 1]) {
            ops += target[i] - target[i - 1];
        }
    }                                                    
    return ops;
}

int main(int argc, char* argv[]) {
	int nums[100], n;
	readArgs(argc, argv, "#d", nums, &n);
	printf("%d\n", minNumberOperations(nums, n));
	return 0;
}
