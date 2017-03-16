#include <stdio.h> 
#include <inttypes.h>
#include <stdlib.h>
#include <math.h> 
#include <time.h>
#include <sys/time.h>
#include <locale.h>

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min, int max)
{
    return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

void swap (uint32_t *a, uint32_t *b) {
	uint32_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void int_dec_selection_sort(uint32_t *arr, uint32_t n)
{
	for (int i = 0; i < n - 1; i++) {
		uint32_t min = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[min] > arr[j]) {
				min = j;
			}
		}
		if (min != i) {
			swap(&arr[min], &arr[i]);
		}
	}
}

void gen_rand_arr(uint32_t **arr, uint32_t n)
{
	*arr = calloc(n, sizeof(uint32_t));
	srand(time(0));
	for (int i = 0; i < n; i++) {
		(*arr)[i] = getrand(0, 100001);
	}
}

int valid_sort(uint32_t *arr, uint32_t n)
{
	for (int i = 0; i < n - 1; i++) {
		if (arr[i] > arr[i+1]) {
			return 0;
		}
	}
	return 1;
}

int main()
{
	for (int i = 1; i <= 20; i++) {
		uint32_t *a;
		int n = 50000 * i;
		gen_rand_arr(&a, n);
		double t;

		t = wtime();

		int_dec_selection_sort(a, n);

		t = wtime() - t;

		setlocale(LC_NUMERIC,"");
		printf("Elapsed time: elements: %d\t%.6f sec.\n", n, t);  
		
		free(a);
	}
	return 0;
}