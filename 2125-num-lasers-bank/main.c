#include "..\readargs.h"
#include <string.h>

int numberOfBeams(char** bank, int n) {
	int cnt[n];
	memset(cnt, 0, sizeof cnt);
	int m = strlen(bank[0]);
	int i;
    for (i = 0; i < n; i++) {
		char* row = bank[i];
		for (int j = 0; j < m; j++) {
			if (row[j] == '1') cnt[i]++;
		}
	}
	int prev = -1;
	int total = 0;
	for (i = 0; i < n; i++) {
		if (cnt[i] > 0) {
			if (prev != -1) {
				total += prev * cnt[i];
			}
			prev = cnt[i];
		}
	}
	return total;
}

int main(int argc, char* argv[]) {
	char* bank[10];
	int n;
	readArgs(argc, argv, "#s", bank, &n);
	printf("%d\n", numberOfBeams(bank, n));
	return 0;
}
