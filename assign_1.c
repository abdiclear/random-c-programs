/*
Name: Habib Mohamed
Date: July 11, 2017
Purpose: This program will fill a 2D array NxM with random integers. It will then proceed to sort it by descending order, before taking
         a user input and searching for that input in the 2D array. 
*/

//We will need the latter two libraries to fill the 2D array with random integers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//The dimensions of the array will be constant
#define COL 20
#define ROW 20

/*
This function will sort the contents in a 2D array in descending order
The inputs are the 2D array, the row and column sizes
The output is the sorted array
*/
int SortMatrix(int A[ROW][COL], unsigned int rowsize, unsigned int colsize);

/*
This function will search for a number defined by the user
The inputs are the 2D array, the number the user wants, a 1D array to hold the location of number, the row and column sizes
The output will be a 1D array either containing the coordinates of the desired number, or -1,-1 if the number wasn't found
*/
int SearchMatrix(int A[ROW][COL], int V, int *P, unsigned int rowsize, unsigned int colsize);

/*
The main function will first fill a 2D array with random integers, then sort it descending, before finally asking the user
for a number they want to search, then searching for it through array.
The input is the desired-by-user number
The output is whether the number is found, and the coordinates if it is
*/
int main(void){
	
	//Initializing the 2D array
	int matrix[ROW][COL];
	
	
	//This will be used to hold the number the user wants to search for
	int searchnum;
	
	//This array will be used to hold the coordinates of the number in the matrix if found
	int coordinates[2];
	
	//Setting up a seed for our random integer generator
	srand(time(NULL));

	
	//Filling the array with random integers
	for(int i = 0; i < ROW ; i++){
		for(int j = 0; j < COL; j++){
			matrix[i][j] = rand() % 100;
		
		}
	}
	
	
	//Sort the matrix by descending order
	SortMatrix(matrix, ROW, COL);
	
	
	
	//Asks the user what number they want to search for and obtains it from them
	printf("What number do you want to search for from 0-100?\n");
	scanf("%d", &searchnum);
	
	//Searches the matrix for the number
	int isFound = SearchMatrix(matrix, searchnum, coordinates, 0, 19);
	
	//Reports results to user.
	if(isFound == 1){
		
		printf("The number is located at %d, %d\n", coordinates[0], coordinates[1]);
		
	}else if(isFound == -1){
		
		printf("The number has not been found.");
		
	}
	
	
}



int SortMatrix(int A[ROW][COL], unsigned int rowsize, unsigned int colsize){
	
	int rowpass, colpass, K; //rowpass is for going through rows, colpass for columns, and K for 1D passes
	int temp; //Will be used to hold values during swaps
	int arraysize = rowsize * colsize; //For number of cells in array
	int array[arraysize]; //This is a 1D array 
	
	//This will be used to put numbers 1 by 1 in 1D array
	int i = 0;
	
	//This sends the contents of the 2D array into a 1D array
	for(rowpass = 0; rowpass < rowsize; rowpass++){
		for(colpass = 0; colpass < colsize; colpass++){
			array[i] = A[rowpass][colpass];
			i++;
		}
	}

	//A bubble sort is peformed on the 1D array, sorting it in descending order
	for(int pass = 0; pass < (arraysize - 1); pass++){
		for(K = 0; K < (arraysize - 1); K++){
			
			if(array[K] < array[K+1]){
				
				temp = array[K];
				array[K] = array[K+1];
				array[K+1] = temp;
				
			}
			
		}
	}
	
	//This is used to send put numbers 1 by 1 into a 2D array
	int z = 0;
	
	//This puts the contents of the sorted 1D array into the 2D array
	for(rowpass = 0; rowpass < rowsize; rowpass++){
		for(colpass = 0; colpass < colsize; colpass++){
			A[rowpass][colpass] = array[z];
			z++;
			
		}
		
	}
	
	return 0;
}

int SearchMatrix(int A[ROW][COL], int V, int *P, unsigned int rowsize, unsigned int colsize){
	
	//If the rowsize and colsize go beyond the parameters of 0 and 19, the number hasnt been found.
	if((rowsize > (ROW - 1) || rowsize < 0) || (colsize < 0 || colsize > (COL - 1))){
		
		P[0] = -1;
		P[1] = -1;
		return -1;
	}
	
	//If the number has been found at the array cell, then the cell coordinated are placed in a 1D array
	if(V == A[rowsize][colsize]){
		
		P[0] = rowsize; 
		P[1] = colsize;
		return 1;
		
	}else{
		
		//If the number is greater than the number at the specified cell, we look at the adjacent cell to the left
		if(V > A[rowsize][colsize]){
			
			return SearchMatrix(A, V, P, rowsize,  colsize - 1);
		
		//If the number is lower than the number at the specified cell, we look at the number below the cell.		
		}else if (V < A[rowsize][colsize]){
			
			return SearchMatrix(A, V, P, rowsize + 1, colsize);
			
		}
		
	}
	
}