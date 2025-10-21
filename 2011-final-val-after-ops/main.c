#define _CRT_SECURE_NO_WARNINGS

int finalValueAfterOperations(char** operations, int operationsSize) {
	int x = 0;
	for (int i = 0; i < operationsSize; i++) {
		if (operations[i][1] == '+') x++;
		else x--;
	}
	return x;
}

int main(int argc, char* argv[]) {
	finalValueAfterOperations(argv + 1, argc - 1);
	return 0;
}
