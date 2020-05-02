#include <stdio.h>
#include <time.h>  
#define SIZE 32

void matrix_string(int arr[][SIZE]){
	//int arr[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			arr[i][j] = 1;
		}
	}
}



void matrix_row(int arr[][SIZE]){
	//int arr[SIZE][SIZE];
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			arr[j][i] = 1;
		}
	}
}



int main(){
	int arr[SIZE][SIZE];
	struct timespec start, stop; 
	double rez_string, rez_row;

	clock_gettime (CLOCK_REALTIME, &start);
	matrix_string(arr);
	clock_gettime (CLOCK_REALTIME, &stop);
	rez_string = 1000000000*(stop.tv_sec - start.tv_sec)+(stop.tv_nsec - start.tv_nsec);
	printf("matrix_string: %.2f нс\n", rez_string);

	clock_gettime (CLOCK_REALTIME, &start);
	matrix_row(arr);
	clock_gettime (CLOCK_REALTIME, &stop);
	rez_row = 1000000000*(stop.tv_sec - start.tv_sec)+(stop.tv_nsec - start.tv_nsec);
	printf("matrix_row: %.2f нс\n", rez_row);

	printf("diff: %.2f %% \n", (rez_row/rez_string)*100 - 100);
	
	return 0;
}