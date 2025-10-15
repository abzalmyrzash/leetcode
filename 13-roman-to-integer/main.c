#include <stdio.h>

int romanToInt(char* s) {
	int num = 0;
	int i = 0;
	while (s[i] == 'M') {
		num += 1000;
		i++;
	}

	if (s[i] == 'C') {
		if (s[i + 1] == 'M') {
			num += 900;
			i += 2;
		} else if (s[i + 1] == 'D') {
			num += 400;
			i += 2;
		} else {
			do {
				num += 100;
				i++;
			} while (s[i] == 'C');
		}
	}
	else if (s[i] == 'D') {
		num += 500;
		i++;
		while (s[i] == 'C') {
			num += 100;
			i++;
		}
	}

	if (s[i] == 'X') {
		if (s[i + 1] == 'C') {
			num += 90;
			i += 2;
		} else if (s[i + 1] == 'L') {
			num += 40;
			i += 2;
		} else {
			do {
				num += 10;
				i++;
			} while (s[i] == 'X');
		}
	}
	else if (s[i] == 'L') {
		num += 50;
		i++;
		while (s[i] == 'X') {
			num += 10;
			i++;
		}
	}

	if (s[i] == 'I') {
		if (s[i + 1] == 'X') {
			num += 9;
			i += 2;
		} else if (s[i + 1] == 'V') {
			num += 4;
			i += 2;
		} else {
			while (s[i] == 'I') {
				num += 1;
				i++;
			}
		}
	}
	else if (s[i] == 'V') {
		num += 5;
		i++;
		while (s[i] == 'I') {
			num += 1;
			i++;
		}
	}

    return num;
}


int main (int argc, char* argv[]) {
	if (argc != 2) return 1;
	printf("%d\n", romanToInt(argv[1]));
}
