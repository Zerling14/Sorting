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

void heapify (uint32_t *arr, int pos, int n) {
    while (2 * pos + 1 < n) {
        
        int t = 2 * pos +1;
        if (2 * pos + 2 < n && arr[2 * pos + 2] >= arr[t])
        {
            t = 2 * pos + 2;
        }
        if (arr[pos] < arr[t]) {
            swap(&arr[pos], &arr[t]);
            pos = t;
        } 
        else break;
        
    }
}

void heap_make(uint32_t *arr, int n)
{
    for (int i = n - 1; i >= 0; i--)
    {
        heapify(arr, i, n);
    }
}
void heap_sort(uint32_t *arr, int n)
{
    heap_make(arr, n);
    while(n>0)
    {
        swap(&arr[0], &arr[n-1]);
        n--;
        heapify(arr, 0,n);
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

		heap_sort(a, n);

		t = wtime() - t;
		
		setlocale(LC_NUMERIC,"");
		printf("Elapsed time: elements: %d\t%.6f sec.\n", n, t);  
		
		free(a);
	}
	return 0;
}