#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

bool isPalindrome(int x) {
	if (x < 0) return false;
	int y = x;
	int rev = 0;
	while (x) {
		rev = rev * 10 + x % 10;
		x /= 10;
	}
    return y == rev;
}

int main() {
	int x;
	scanf("%d", &x);
	printf("%d\n", isPalindrome(x));
}
