#include <stdio.h>
#include <math.h>

int main() {
	int A[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	double avg;
	size_t length = sizeof(A) / sizeof(A[0]);

	for (size_t i = 0; i < length; i++) {
		avg += sqrt(A[i]);
	}
	printf("The average is %lf\n", avg);
	return 0;
}


