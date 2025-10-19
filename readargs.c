#define _CRT_SECURE_NO_WARNINGS
#include "readargs.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct ListNode {
	int val;
	struct ListNode* next;
} ListNode;

int readArgs(int argc, char* argv[], char* fmt, ...) {
	va_list args;
	int i = 0;
	bool readArg = true;
	bool isArr = false, isLinked = false;

	for (va_start(args, fmt); *fmt != '\0'; ++fmt) {
		if (readArg) {
			i++;
			if (i == argc) {
				va_end(args);
				if (*fmt != '\0') {
					fprintf(stderr, "Unprocessed args: %s\n", fmt);
					return 1;
				} else return 0;
			}
		} else readArg = true;

		switch(*fmt) {
			case 'd':
				if (isArr) {
					int* arr = va_arg(args, int*);
					int* size = va_arg(args, int*);
					*size = 0;
					int charsRead, offset = 0;
					while(1 == sscanf(argv[i] + offset, "%*c%d%n",
								&arr[*size], &charsRead)) {
						(*size)++;
						offset += charsRead;
					}
				} else if (isLinked) {
					ListNode* dummyHead = va_arg(args, ListNode*);
					ListNode* node = dummyHead;
					int charsRead, offset = 0;
					int num;
					while(1 == sscanf(argv[i] + offset, "%*c%d%n",
								&num, &charsRead)) {
						node->next = malloc(sizeof(ListNode));
						node = node->next;
						node->val = num;
						offset += charsRead;
					}
					node->next = NULL;
				} else {
					int* n = va_arg(args, int*);
					sscanf(argv[i], "%d", n);
				}
				break;

			case 's':
				if (isArr) {
					char*** s = va_arg(args, char***);
					*s = argv + i;
					va_end(args);
					return 0;
				} else if (isLinked) {
					va_end(args);
					return 0;
				} else {
					char** s = va_arg(args, char**);
					*s = argv[i];
				}
				break;

			default:
				readArg = false;
				if (*fmt != '#' && *fmt != '*' && *fmt != ' ') {
					fprintf(stderr, "Invalid format character: %c\n", *fmt);
					va_end(args);
					return 1;
				}
				break;
		}
		isArr = (*fmt == '#');
		isLinked = (*fmt == '*');
	}
	va_end(args);
	return 0;
}
