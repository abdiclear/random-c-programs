/*
Name: Habib Mohamed
Date: July 20, 2017
Purpose: This takes in a maximum of 10 lines of words (max 80 characters each), and counts how many times a letter occurs,
		 the lengths of words, and the number of occurences of a word.
*/

//These libraries will be necessary for our purpose
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//Sets limits for number of characters and lines
#define CHARS 80
#define LINES 10

/*
This counts how many times each letter of the alphabet occurs in a given text
It takes in a 2D array with text and the number of text lines
Yields a 2D array of letters and the number of times they occur
*/
void letterAnalysis(char array [LINES][CHARS], int *linenum){
	
	int occurArray[26][2] = {0}; //This will hold each letter and the number of its occurences
	
	//The left column of the array will hold all the letters (lowercase) of the alphabet
	for(int i = 97, k = 0; i < 123; i++, k++){
		
		occurArray[k][0] = i;
		
	}
	
	int z = 0; //This will be used to parse through the rows of occurArray
	
	//This loop gows through the rows of the 2D array containing the text
	for(int x = 0; x <= *linenum; x++){
		
		//This looks at each character in a row until it hits a new line character
		for(int y = 0; !iscntrl(array[x][y]); y++){
			
			//This goes through the whole alphabet searching for a match. It account for both upper and lower case.
			for(char w = 65, p = 97; (w < 91 || p < 123); w++, p++){
				
				//If there is a match in letters, its respective counter in occurArray is incremented
				if(array[x][y] == w || array[x][y] == p){
					
					occurArray[z][1]++;
					
					
				}
				z++;//This helps move down the rows of occurArray, matching respective letters
			}
			z = 0;//When the whole alphabet is parsed through, z is set back to 0
		}
		
	}
	
	//The results of the letter counting is output to user.
	printf("Total letter counts:\n");
	
	for(int j = 0; j < 26; j++){
		
			printf("%c:\t", occurArray[j][0]);
			printf("%d\n", occurArray[j][1]);
		
		
	}
	
}

/*
This counts how many times n-length words occur in a given text
A 2D array containing text and the number of text lines are supplied to this function
Yields a 2D array with number of occurences to corresponding word lengths
*/
int wordLengthAnalysis(char array[LINES][CHARS], int *linenum){
	
	int wordArray[20][2] = {0}; //This will be a table of 1-20 length words, and how many times they occur
	
	//The left column of the array will hold numbers 1-20
	for(int k = 0, i = 1; k < 20; i++, k++){
		
		wordArray[k][0] = i;
		
	}
	
	int length = 0;//This will be used to deduce word lengths

	
	//This loop gows through the rows of the 2D array containing the text
	for(int x = 0; x <= *linenum; x++){
		
		//This looks at each character in a row until it hits a new line character
		for(int y = 0; !iscntrl(array[x][y]); y++){
			
			//If the character we are looking at is end-line, white-space, or punctuation:
			if(isspace(array[x][y]) || iscntrl(array[x][y]) || ispunct(array[x][y])){
				
				//We increment the cell tracking the number of words with length
				for(int n = 0; n < 20; n++){
					
					if(wordArray[n][0] == length)
						wordArray[n][1]++;
					
				}
				
				length = 0;//Length is set to 0, as a word has been made note of in wordArray
				
			}else{
				
				length++;//We are looking at a character, and thus we increment length
				
			}		
		}
		length = 0;//Once we hit an end-line character, we set length back to 0, as we ae entering a new line
	}
	
	//The following outputs the contents of wordArray. The output varies slightly depending on whether the length is 1 or not.
	printf("\nWord lengths:\n");
	
	for(int j = 0; j < 20; j++){
		
		if(wordArray[j][1] == 1)
			printf("%d\tword of length %d\n", wordArray[j][1], wordArray[j][0]);
		else
			printf("%d\twords of length %d\n", wordArray[j][1], wordArray[j][0]);
		
	}
	
	return 0;
}

/*
This searches for word occurences, and how many times they appear in a given text
Takes in a 2D array with text and the number of text lines
Returns words and the number of times they appear in the text
*/
void wordAnalysis(char array[LINES][CHARS], int *linenum){
	
	char words[800][20] = {0};//This will hold each word from the text
	
	int wordrow = 0; //This insures each word from the text is separate
	int wordcol = 0; //This puts characters of each word one by one into a row
	
	//This loop gows through the rows of the 2D array containing the text
	for(int x = 0; x <= *linenum; x++){
		
		//This looks at each character in a row until it hits a new line character
		for(int y = 0; !iscntrl(array[x][y]); y++){
			
			//If the character we are looking at is end-line, white-space, or punctuation:
			if(isspace(array[x][y]) || iscntrl(array[x][y]) || ispunct(array[x][y])){
				
				words[wordrow][wordcol] = '\0'; //We put the null character into the cell to signal a string
				wordrow++; //We move on to a new row to hold a new word
				wordcol = 0; //We start from the first column
				
			}else{
				
				words[wordrow][wordcol] = array[x][y]; //We put in the character
				wordcol++; //We move on to the next column
				
			}		
		}
		
		wordrow++; //We move on to a new row to hold a new word, this is for end-line scenarios
		wordcol = 0; //We start from the first column
		
	}
	
	char null[20] = {0}; //This is intended to be an empty array
	char hold[20] = {0}; //This will hold words from the word array
	int occur = 0; //This counts how many times a word occurs
	
	printf("\nWord occurences:\n");
	
	//This goes through each row of the word array
	for(int j = 0; j < wordrow; j++){
		
		//If the row we are looking at is not empty
		if(strcmp(words[j], "") != 0){
			
			strcpy(hold, words[j]); //We store the word into hold
			occur++; //We increment the occur counter
			
			//We check to see if the word in hold occurs again
			for(int k = j + 1; k < wordrow; k++){
				
				//If it does, we set the repeated word to empty space and the occur counter is incremented
				if(strcmp(hold, words[k]) == 0){
					
					strcpy(words[k], null);
					occur++;
					
				}
				
			}
			if(occur == 1) //The output is slightly different depending on the value of occur
				printf("\"%s\"\tappeared %d time\n", hold, occur);
			else
				printf("\"%s\"\tappeared %d times\n", hold, occur);
			
			strcpy(hold, null); //hold is emptied
			occur = 0; //occur counter is reset
			
			
		}
		
		
		
	}
	
}

/*
This takes the words from user and places it in a 2D array
A 2D array is taken in as input, along with number of lines
A filled 2D array is yielded, along with updated number of lines
*/
void fillByInput(char array [LINES][CHARS], int *linenum){
	
	
	printf("How many lines do you want to input? Maximum is 10.\n"); //Asks user how many numbers they want to input
	
	scanf("%d", linenum); //Places the input into int lines
	
	printf("Ok. %d lines to be analyzed. You may start typing.\n", *linenum);
	
	//This for loop takes in user input untill lines number of sentences have been input
	for(int i = 0; i <= *linenum; i++)
		gets(array[i]);
	
	
}

/*
This takes the words from a file and places it in a 2D array
A 2D array is taken in as input, along with number of lines
A filled 2D array is yielded, along with updated number of lines
*/
void fillByFile(char array[LINES][CHARS], int *linenum){
	
	char filename[20]; //This will hold the name of the file
	
	char lines[1]; //Used to hold number of lines
	
	printf("What is the name of the file you want to read from?\n"); //Asks user what file they want to read
	
	scanf("%s", filename); //Reads user input
	
	FILE *fp = fopen(filename, "r"); //Directs input stream to file
	
	fscanf(fp, "%s", lines); //Reads for number of lines
	
	*linenum = atoi(lines); //The number that was read from first line of the file is conveted from string to integer
	
	//This puts each line of text in file in each array line
	for(int i = 0; i <= *linenum; i++){
	
		fgets(array[i], CHARS, fp);

	}

	fclose(fp); //Redirects stream back to default
	
	
}

/*
*/
int main(){
	
	char text[LINES][CHARS]; //This will be used to hold text
	
	int linesnum = 0; //The number of lines of the text will define how many rows of the above array will be used
	
	int option; //This is used to give the user the option to read from file or type in text
	
	printf("Would you like to: 1) type in text, or 2) get text from file?\n"); //Asks user what they want to do
	
	scanf("%d", &option); //User input is read
	
	//This will get data based on user input
	switch(option){
		
		case 1: //If input is 1, we take in user input and run assorted functions on it
		fillByInput(text, &linesnum);
		letterAnalysis(text, &linesnum);
		wordLengthAnalysis(text, &linesnum);
		wordAnalysis(text, &linesnum);
		break;
		
		case 2: //If input is 2, we read from user-specified file and run assorted functions on it
		fillByFile(text, &linesnum);
		letterAnalysis(text, &linesnum);
		wordLengthAnalysis(text, &linesnum);
		wordAnalysis(text, &linesnum);
		break;
		
		default: //If input is not 1 or 2
		printf("Please type in 1 or 2 according to the order of what you want.\n");
		
	}
	
}
