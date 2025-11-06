#include "readargs.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct ListNode {
	int val;
	struct ListNode* next;
} ListNode;

int readArgs(int argc, char* argv[], char* fmt, ...) {
	va_list vargs;
	int i = 0;
	bool readArg = true;
	bool isArr = false, isLinked = false;

	for (va_start(vargs, fmt); *fmt != '\0'; ++fmt) {
		if (readArg) {
			i++;
			if (i == argc) {
				va_end(vargs);
				if (*fmt != '\0') {
					fprintf(stderr, "Unprocessed vargs: %s\n", fmt);
					return 1;
				} else return 0;
			}
		} else readArg = true;

		char* arg = argv[i];
		int len = strlen(arg);

		switch(*fmt) {
			case 'd':
				if (isArr) {
					int* arr = va_arg(vargs, int*);
					int* size = va_arg(vargs, int*);
					*size = 0;
					int charsRead, offset = 0;
					while(1 == sscanf(arg + offset, "%*c%d%n",
								&arr[*size], &charsRead)) {
						(*size)++;
						offset += charsRead;
					}
				} else if (isLinked) {
					ListNode* dummyHead = va_arg(vargs, ListNode*);
					ListNode* node = dummyHead;
					int charsRead, offset = 0;
					int num;
					while(1 == sscanf(arg + offset, "%*c%d%n",
								&num, &charsRead)) {
						node->next = malloc(sizeof(ListNode));
						node = node->next;
						node->val = num;
						offset += charsRead;
					}
					node->next = NULL;
				} else {
					int* n = va_arg(vargs, int*);
					sscanf(arg, "%d", n);
				}
				break;

			case 's':
				if (isArr) {
					char** arr = va_arg(vargs, char**);
					int* size = va_arg(vargs, int*);
					int cnt = 0;
					bool isEscape = false;
					if (*arg == '[') arg++;
					if (*arg == '\0') break;
					arr[cnt++] = arg;
					while (*arg != '\0') {
						if (*arg == ',' || *arg == ']') {
							*arg = '\0';
							if (*(arg + 1) == '\0') break;
							arr[cnt++] = arg + 1;
						}
						arg++;
					}
					*size = cnt;
				} else if (isLinked) {
					printf("String linked list not yet implemented\n");
					va_end(vargs);
					return 0;
				} else {
					char** s = va_arg(vargs, char**);
					*s = arg;
				}
				break;

			default:
				readArg = false;
				if (*fmt != '#' && *fmt != '*' && *fmt != ' ') {
					fprintf(stderr, "Invalid format character: %c\n", *fmt);
					va_end(vargs);
					return 1;
				}
				break;
		}
		isArr = (*fmt == '#');
		isLinked = (*fmt == '*');
	}
	va_end(vargs);
	return 0;
}
