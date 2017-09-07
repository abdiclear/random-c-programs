/*
Name: Habib Mohamed
Date: July 24, 2017
Purpose: This takes course information from a file, puts it in a structure, and allows the user to update it, search it, and view it
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//A structure is declared here with the course information as fields. An alias is defined here.
typedef struct CourseInfo{
		
		int CourseID;
		char courseName[50];
		char courseCode[12];
		char Term[6];
		
	} Data;
	
	Data course[50] = {0}; //We define an array of structures

/*
This takes the contents of input.csv and put it into the structure CourseInfo
Takes in the file name and the number of contents as inputs
Returns a filled structure	
*/
void loadCourseInfo(int *contents){
	
	char filename[] = "input.csv"; //This will hold the name of the file
	
	char lines[1]; //Used to hold number of lines
	
	FILE *fp = fopen(filename, "r"); //Directs input stream to file
	
	fscanf(fp, "%s", lines); //Reads for number of lines
	
	*contents = atoi(lines); //The number that was read from first line of the file is conveted from string to integer
	
	char hold[1] = {0}; //This will be used to hold course ids
	
	//This puts each line of text in file in each array line
	for(int i = 0; i < *contents; i++){
		
		fscanf(fp, "%s %s %s %s", hold, course[i].courseName, course[i].courseCode, course[i].Term); //A line of course info is read and stored, except for the ID field
		
		course[i].CourseID = atoi(hold); //Since the id field is an int, we convert the char array holding it to an int
	
	}

	
	fclose(fp); //Redirects stream back to default
}

/*
This saves the contents of a structure into a file
Takes in the file name and the number of contents
Stores the structure's contents into a file
*/
void saveCourseInfo(int *contents){
	
	char filename[] = "input.csv"; //This will hold the name of the file
	
	FILE *fp = fopen(filename, "w"); //Directs input stream to file
	
	fprintf(fp, "%d\n", *contents); //Print out number of lines
	
	//This puts course info in file line by line
	for(int i = 0; i < *contents; i++){
		
		fprintf(fp, "%d %s %s %s\n", course[i].CourseID, course[i].courseName, course[i].courseCode, course[i].Term); //A line of course info is read and stored, except for the ID field
	
	}

	
	fclose(fp); //Redirects stream back to default
	
}

/*
This prints out the contents of the structure CourseInfo
This takes in the number of courses as input
Prints out to the user the data in the structure
*/
void displayCourseInfo(int *contents){
		
	//This goes through each record in the structure and outputs it to user
	for(int i = 0; i < *contents; i++){
		
		printf("%d, %s, %s, %s\n", course[i].CourseID, course[i].courseName, course[i].courseCode, course[i].Term);
		
		
	}
	
}

/*
This adds in course information according to user input
Takes in user input on new course
Stores in structure and calls a loading function to store it in the file as well 
*/
void addCourseInfo(int *contents){
	
	course[*contents].CourseID = (*contents + 1); //The course ID is automatically updated
	
	char check[50]; //Will hold the user input on course code
	
	int similar = 0; //Checks for similarity
	
	printf("Enter the course code\n"); //Asks user to input course code
	
	scanf("%s", check); //Stores user input in check
	
	//Goes through the course codes in the structure. If a match is found, similar is set to 1.
	for(int i = 0; i < *contents; i++){
		
		if(strcmp(check, course[i].courseCode) == 0)
			similar = 1;
		
	}
	
	//If similar is not 1, the user is prompted for the rest of the course information, which is stored in structure. The number of courses is updated.
	if(similar == 0){
		
		strcpy(course[*contents].courseCode, check);
		
		printf("Enter the course name\n");
		
		scanf("%s", course[*contents].courseName);
		
		printf("Enter the course term\n");
		
		scanf("%s", course[*contents].Term);
		
		*contents += 1;
		
		printf("Course has been added.\n");
		
	}else{ //If similar is 1, the user is told that the course code exists. The work done on course ID is undone.
		
		printf("The course code you entered already exists. Type in a new one.\n");
		
		course[*contents].CourseID = 0;
		
		
	}
	
	
	
}

/*
This searches the structure based on user input on course name or ID.
Takes in user input on name or ID
Returns course information if found or sends user a message if not found
*/
void searchCourseInfo(int *contents){
	
	int option; //This will determine whether the user wants to search by name or ID
	
	int found = 0; //This will determine whether there is a match in the structure
	
	//The user is prompted for input, which is stored in option
	printf("Would you like to search via 1) Course name or  2) Course ID?\n");
	scanf("%d", &option);
	
	//If option is 1, user wants to search by name
	if(option == 1){
		
		//The name the user wants to search for is stored in a char array
		char name[50]; 
		printf("Type in the name of the course you want to search for:\n");
		scanf("%s", name);
		
		//The loop goes through the course names
		for(int i = 0; i < *contents; i++){
			
			//If a match is found, the course information is returned to the user, and found is set to 1.
			if(strcmp(name, course[i].courseName) == 0){
				
				printf("Here is the course information you were looking for:\n");
				
				printf("%d, %s, %s, %s\n", course[i].CourseID, course[i].courseName, course[i].courseCode, course[i].Term);
				
				found = 1;
				
			}
			
		}
		
		//If found is 0, that means there was no match, and the user is told such
		if(found == 0)
			printf("The course name you were searching for has not been found.\n");
		
	}else if (option == 2){
		
		//The name the user wants to search for is stored in a int variable
		int id; 
		printf("Type in the ID of the course you want to search for:\n");
		scanf("%d", &id);
		
		//The loop goes through the course IDs
		for(int i = 0; i < *contents; i++){
			
			//If a match is found, the course information is returned to the user, and found is set to 1.
			if(course[i].CourseID == id){
				
				printf("Here is the course information you were looking for:\n");
				
				printf("%d, %s, %s, %s\n", course[i].CourseID, course[i].courseName, course[i].courseCode, course[i].Term);
				
				found = 1;
				
			}
			
		}
		
		//If found is 0, that means there was no match, and the user is told such
		if(found == 0)
			printf("The course name you were searching for has not been found.\n");
		
	}else{ //If the user inputs a number other than 1 or 2, an error message is sent.
		
		printf("Type in the number associated with your choice.\n");
		
	}
	
}


/*
The main defines the course number variable and calls the above functions in a menu
Takes in user input based on what function they want to call
Output is based on the called functions 
*/
int main(){
	
	int courses = 0; //This will be used to keep count of functions
	
	//We declare the variable we will use to run the menu. We also greet the user, and load the course information from file
	int option = 0;
	printf("Hello! Loading course information.\n");
	loadCourseInfo(&courses);
	
	//The while loop will allow the user to keep running the various functions until they want to stop
	while(option != 4){
		
		//The menu options
		printf("1. Would you like to add a course?\n");
		printf("2. Would you like to print out the course information?\n");
		printf("3. Would you like to search the course list?\n");
		printf("4. Would you like to end the program?\n");
		
		//Gets the user option
		scanf("%d", &option);

		//Directs the user to the functions they want
		switch(option){
			
			//This runs the add course function. The updates are saved in a file.
			case 1: addCourseInfo(&courses);
					saveCourseInfo(&courses);
			break;
			
			//This runs the course info printing function
			case 2: displayCourseInfo(&courses);
			break;
			
			//This runs the course search function
			case 3: searchCourseInfo(&courses);
			break;
			
			//This sends the user a farewell message before terminating the program
			case 4:
			printf("Thanks for using the program.\n");
			break;
			
			//An error message in case the user doesn't input a valid menu option
			default:
			printf("Enter a number 1-4 according to the option you want.\n");
			break;
			
		}
		
	}
	
	
}