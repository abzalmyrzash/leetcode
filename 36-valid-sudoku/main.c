#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
	for (int i = 0; i < 9; i++) {
		bool rows[9] = { false };
		bool cols[9] = { false };
		bool sqrs[9] = { false };
		for (int j = 0; j < 9; j++) {
			if (board[i][j] != '.') {
				int val = board[i][j] - '1';
				if (!rows[val]) rows[val] = true;
				else return false;
			}
			if (board[j][i] != '.') {
				int val = board[j][i] - '1';
				if (!cols[val]) cols[val] = true;
				else return false;
			}
			int row = 3 * (i / 3) + j / 3;
			int col = 3 * (i % 3) + j % 3;
			if (board[row][col] != '.') {
				int val = board[row][col] - '1';
				if (!sqrs[val]) sqrs[val] = true;
				else return false;
			}
		}
	}
	return true;
}

int main(int argc, char** argv) {
	char** board;
	if (argc == 2) {
		FILE* file = fopen(argv[1], "r");
		for (int i = 0; i < 9; i++) {
			char* buffer = malloc(11);
			fgets(buffer, 11, file);
			buffer[9] = '\0';
			board[i] = buffer;
		}
		fclose(file);
	}
	if (argc == 10) {
		board = argv + 1;
	}
	for (int i = 0; i < 9; i++) {
		printf("%s\n", board[i]);
		if (strlen(board[i]) != 9) return 1;
	}
	int colSize = 9;
	printf("%d\n", isValidSudoku(board, 9, &colSize));
}
