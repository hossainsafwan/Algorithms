/*
Assignment 3
*/
#include "funcProtoypes.h"

/*
	Takesn input for all files and shows the menu in a loop
*/

int main(int argc, char **argv) {


	if (argc < 3) { //argc is 1 by deafault due to executable
		return 0;
	}
	char input[100]; //limit of 100 in input
	char userData[100]; //limit of 100 in input

	do{

		printf("\nSelect a program you want to run:\n" );
		printf(" 1.1 Anagram Search Brute Force:\n");
		printf(" 1.2 Anagram Search Presorting Technique:\n" );
		printf(" 2.1 Brute Force String Search\n");
		printf(" 2.2 Horspool Algorithm:\n");
		printf(" 2.3 Boyer-Moore Algorithm:\n" );
		printf(" Enter 'q' to quit\n" );
		scanf("%s",input);
		if(strcmp(input,"1.1") == 0){

			printf("Enter your number:\n");
			scanf("%s", userData);
			bruteForce(argv,userData);
		}
		else if(strcmp(input,"1.2") == 0){

			printf("Enter your number:\n");
			scanf("%s", userData);
			presorting(argv,userData);
		}
		else if(strcmp(input,"2.1") == 0){

			printf("Enter your pattern\n");
			scanf("%s", userData);
			bruteForceStringSearch(argv,userData);

		}
		else if(strcmp(input,"2.2") == 0){

			printf("Enter your pattern:\n");
			scanf("%s", userData);
			horspoolAlgorithm(argv,userData);

		}else if(strcmp(input,"2.3") == 0){

			printf("Enter your pattern:\n");
			scanf("%s", userData);
			boyerMooreAlgorithm(argv,userData);
		}

	} while (strcmp(input,"q") != 0);




	return 0;
}