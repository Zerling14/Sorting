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

// A utility function to get maximum value in arr[]
int getMax(uint32_t *arr, int n)
{
    int mx = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > mx) {
            mx = arr[i];
		}
	}
    return mx;
}
 

void countSort(uint32_t *arr, int n, int exp)
{
    uint32_t *output = calloc(n, sizeof(uint32_t));
    int i, count[10] = {0};
 
    for (i = 0; i < n; i++) {
        count[ (arr[i]/exp)%10 ]++;
	}

    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
	}
 
    for (i = n - 1; i >= 0; i--) {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }
 
    for (i = 0; i < n; i++) {
        arr[i] = output[i];
	}
	
	free(output);
}
 
void radixsort(uint32_t *arr, int n)
{
    int m = getMax(arr, n);
 
    for (int exp = 1; m/exp > 0; exp *= 10) {
        countSort(arr, n, exp);
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
			return i;
		}
	}
	return 0;
}

int main()
{
	for (int i = 1; i <= 20; i++) {
		uint32_t *a;
		int n = 50000 * i;
		gen_rand_arr(&a, n);
		double t;

		t = wtime();

		radixsort(a, n);
		
		t = wtime() - t;
		
		setlocale(LC_NUMERIC,"");
		printf("Elapsed time: elements: %d\t%.6f sec.\n", n, t);  
		
		free(a);
	}
	return 0;
}