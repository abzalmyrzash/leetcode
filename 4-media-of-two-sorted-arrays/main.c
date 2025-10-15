#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <limits.h>

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	int totalSize = nums1Size + nums2Size;

	int iMed1 = (totalSize - 1) / 2;
	int iMed2 = totalSize / 2;
	int med1, med2;

	int i = 0, i1 = 0, i2 = 0;
	int x, x1 = INT_MAX, x2 = INT_MAX;
	if (nums1Size > 0) x1 = nums1[0];
	if (nums2Size > 0) x2 = nums2[0];

	while (1) {
		if (x1 < x2) {
			x = x1;
			i1++;
			if (i1 < nums1Size) x1 = nums1[i1];
			else x1 = INT_MAX;
		} else {
			x = x2;
			i2++;
			if (i2 < nums2Size) x2 = nums2[i2];
			else x2 = INT_MAX;
		}

		if (i == iMed1) med1 = x;
		if (i == iMed2) {
			med2 = x;
			break;
		}
		i++;
	}

    return (double)(med1 + med2) / 2.0;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	int a[n], b[m];
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	for (int i = 0; i < m; i++) {
		scanf("%d", &b[i]);
	}
	printf("%f\n", findMedianSortedArrays(a, n, b, m));
	return 0;
}
