/*
Name: Safwan Hossain
ID: 0918742
Date: 30/03/2020
Assignment 4
*/

#include "funcPrototypes.h"

int main(int argc, char** argv){

	if(argc != 2){
		return 0;
	}

	char input[100]; //limit of 100 in input
	char userData[100];

	do{

		printf("\nSelect a program you want to run:\n" );
		printf(" 1 Search Optimal BST made via Dynamic Programming\n");
		printf(" 2 Search Optimal BST made via Greedy Technique\n" );
		printf(" Enter 'q' to quit\n" );
		scanf("%s",input);
		if(strcmp(input,"1") == 0){

			printf("Enter a key:\n");
			scanf("%s", userData);
			optimalBSTDynamicProgramming(argv[1], userData);
		}
		else if(strcmp(input,"2") == 0){

			printf("Enter a key:\n");
			scanf("%s", userData);
			optimalBSTGreedyT(argv[1], userData);
		}

	} while (strcmp(input,"q") != 0);


	return 0;
}