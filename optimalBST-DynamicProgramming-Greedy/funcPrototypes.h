/*
Assignment 4
*/
#ifndef __SAFWAN_FUNCS__ 
#define __SAFWAN_FUNCS__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct optimalBSTNode TreeNode;

struct optimalBSTNode{
	char * data;
	double avgKeyComp;
	int i;
	int j;
	TreeNode *left;
	TreeNode * right;
};

//optimalBST-DyanmicT
void optimalBSTDynamicProgramming(char* argv, char* userData);
double* calculateMainTableVal(int i, int j, int n, double mainTable[n+2][n+1],double *frequencies);
TreeNode * createTree(int i, int j, int n,  TreeNode*root, char data [2045][30], double mainTable[n+2][n+1], int rootTable[n+2][n+1]);

//optimalBST-GreedyT
void optimalBSTGreedyT(char* argv, char* userData);
void createTreeGreedy(int i, int j,int n, TreeNode*root, char data [2045][30], double frequencies[2045]);
int findGreatestProbIndex(double frequencies [2045], int i,int j);

#endif

