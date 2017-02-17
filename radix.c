#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h> 

int digit(int n, int j) 
{ 
	return n / (int)pow(10,j) % 10; 
} 

int main() 
{ 
	int i, j, t, k = 10, n = 10; 
	int a[n], b[n], c[k]; 
	srand(time(0)); 


	for (i = 0; i < n; i++) 
		a[i] = rand() % 1000; 

	for (i = 0; i < 3; i++){ 

		for (j = 0; j < k; j++) 
			c[j] = 0; 

		for(j = 0; j < k; j++) 
			c[digit(a[j],i)]++; 

		for(j = 1; j < k; j++) 
			c[j] += c[j - 1]; 

		for(j = n-1; j >= 0; j--) 
			b[--c[digit(a[j],i)]] = a[j]; 

		for (j = 0; j < n; j++) 
			printf("%d ",a[j]); 
		printf("\n"); 

		for (j = 0; j < n; j++) 
			printf("%d ",c[j]); 
		printf("\n"); 

		for (j = 0; j < n; j++) 
			printf("%d ",b[j]); 
		printf("\n"); 
		printf("\n"); 

		for (j = 0; j < n; j++) 
			a[j] = b[j]; 
	} 

	return 0; 
}