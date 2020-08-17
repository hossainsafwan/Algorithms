/*
Function Prototypes
*/
#ifndef __SAFWAN_FUNCS__ 
#define __SAFWAN_FUNCS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/timeb.h>

//bruteforce-anagram.h
void bruteForce(char **argv,char *userData);
int counter(char *str,char c);
int AngramOrNot(int *numOfEachDigitUser,int *numOfEachDigitDataFile);

//presorting-anagram.h
void presorting(char **argv,char *userData);

//bruteforce.h
 void bruteForceStringSearch(char **argv,char *userData);

 //horspool.h
void createTable(char *userData, int table[256]);
void horspoolAlgorithm(char **argv,char *userData);
int horspoolMatching(char * userData, char *readLine, int i,int m,int table[256]);

//boyerMoore.h
int boyerMooreMatching(char * userData, char *readLine, int i,int m);
void boyerMooreAlgorithm(char **argv,char *userData);
void createTableBoyerMoore( char *str, int size, int table2[256]);
int findMax (int a, int b);

#endif

