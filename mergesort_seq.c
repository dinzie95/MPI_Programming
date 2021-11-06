#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// Merges two subarrays of arr[].
void merge(int arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	//temp arrays
	int L[n1], R[n2];

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of L[], if any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of R[], if any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort(int arr[],int l,int r){
	if(l>=r){
		return;
	}
	int m =l+ (r-l)/2;
	mergeSort(arr,l,m);
	mergeSort(arr,m+1,r);
	merge(arr,l,m,r);
}


void printArray(int A[], int size)
{
	for (int i = 0; i < size; i++){
		printf("%d ", A[i]);
	}
	printf("\n");	
}

//Main Function
int main(int argc, char** argv)
{
	
	clock_t start_time;
	clock_t end_time;
	double duration;	

	//Create an array with random numbers from 1-100
	int array_size = atoi(argv[1]);
	int *number_array = (int*)malloc(array_size * sizeof(int));
	
	int c;
	srand(time(NULL));
	for(c = 0; c < array_size; c++) {
		number_array[c] = rand() % 100;
		}

	//First 10 elements are printed to prevent inconvenice caused with larger arrays
	printf("First 10 elements of unsorted array: ");
	for(c = 0; c < 10; c++) {
		printf("%d ", number_array[c]);
	}
	
	printf("\n\n");

	start_time = clock();//start time
	mergeSort(number_array, 0, array_size - 1);
	end_time = clock();//end time

	//First 10 elements are printed to prevent inconvenice caused with larger arrays
	printf("First 10 elements of Sorted array: ");
	printArray(number_array, 10);

	duration = ((end_time-start_time)/(double)CLOCKS_PER_SEC);
	printf("Execution time: %f s\n",duration);
	return 0;
}

