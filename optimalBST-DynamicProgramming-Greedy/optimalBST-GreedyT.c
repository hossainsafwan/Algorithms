/*
Name: Safwan Hossain
ID: 0918742
Date: 30/03/2020
Assignment 4
*/

#include "funcPrototypes.h"
/*
parses the data_7.txt file calculates frequencies
and searches for the key
*/
void optimalBSTGreedyT(char* argv, char* userData){

	char words [2500][30]; 
	char data [2045][30]; 
	double frequencies[2045] = {0.0};
	char line [3000];
	char *token;
	
	FILE *fp = fopen(argv,"r");

	if(fp != NULL) {
		int wordCount = 0;

		//parse words
		while(fgets(line, 3000, fp) != NULL){
			token = strtok(line, " ");
			while(token){
				if(strcmp(token,"\0") != 0 && strcmp(token,"\n") != 0){
					strcpy(words[wordCount],token);
					wordCount++;
				}
				token = strtok(NULL, " ");
			}
			
		}

		//remove repetations and any special characters and copy to data[][]
		int addCount=1;
		int match =-1; //0 == match
		for(int i=0;i<wordCount;i++){
			for(int j=0;j<addCount;j++){

				if(strcmp(data[j],words[i]) == 0 ||
				 (words[i][0] >= 0 &&  words[i][0] <= 64) || 
				  (words[i][0] >= 91 &&  words[i][0] <= 96 ) ||
				  (words[i][0] >= 123)){
					match = 0;
				}
			}

			if(match == -1){
				strcpy(data[addCount-1],words[i]);
				addCount++;
			}else{
				match=-1;
			}
		}

		//calculate frequencies
		for(int i =0;i<addCount;i++){
			for(int j=0;j<wordCount;j++){
				if(strcmp(data[i],words[j]) == 0){
					frequencies[i] = frequencies[i]+1;
				}
			}

		}

		//arrange data and frequencies in alphabetical order
		char temp[30];
		int tempFreq;

		for(int i=0; i<addCount-1;i++){
			for(int j=i+1;j<addCount-1;j++){
				if(strcmp(data[i],data[j]) > 0){
					strcpy(temp,data[i]);
					tempFreq = frequencies[i];
					
					strcpy(data[i],data[j]);
					frequencies[i] = frequencies[j];
					
					strcpy(data[j],temp);
					frequencies[j] = tempFreq;
				}
			}
		}

		int n = addCount-1; //number of keys
		
		int index = findGreatestProbIndex(frequencies,0,n-1);

		TreeNode* root = (TreeNode*) malloc(sizeof(TreeNode));
		root->data = data[index];
		root->avgKeyComp = frequencies[index]/2045;
		root->i=0;
		root->j=n-1;

		createTreeGreedy(0,n-1,n,root,data,frequencies);

		//search
		int found = -1;
		while(found == -1){
			if(root == NULL){
				printf("Not Found\n");
				found=0;
			}else if(strcmp(userData,root->data) == 0){
				printf("Compared with %s (%0.4lf), found.\n", root->data,root->avgKeyComp);
				found = 0;
			}
			else if(strcmp(userData,root->data) < 0){
				printf("Compared with %s (%0.4lf), go left subtree.\n", root->data,root->avgKeyComp);
				root=root->left;
			}
			else if(strcmp(userData,root->data) > 0){
				printf("Compared with %s (%0.4lf), go right subtree.\n", root->data,root->avgKeyComp);
				root=root->right;
			}
		}
	}

}
/*
	Recursively creates optimal binary search tree
*/
void createTreeGreedy(int i, int j,int n, TreeNode*root, char data [2045][30], double frequencies[2045]){

	int rootIndex = findGreatestProbIndex(frequencies,i,j);

	TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));

	if(rootIndex == j){ root->right=NULL; } 
	if(rootIndex == i){ root->left=NULL; } 
	if(rootIndex < j){//right tree
		newNode->data = data[findGreatestProbIndex(frequencies,rootIndex+1,root->j)];
		newNode->avgKeyComp = frequencies[findGreatestProbIndex(frequencies,rootIndex+1,root->j)]/2045;
		newNode->i=rootIndex+1;
		newNode->j=root->j;
		root->right=newNode;
		createTreeGreedy(newNode->i,newNode->j,n,newNode,data,frequencies);
	}
	if(i < rootIndex){//left tree
		TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
		newNode->data = data[findGreatestProbIndex(frequencies,i,rootIndex-1)];
		newNode->avgKeyComp = frequencies[findGreatestProbIndex(frequencies,i,rootIndex-1)]/2045;
		newNode->i=root->i;
		newNode->j=rootIndex-1;
		root->left=newNode;
		createTreeGreedy(newNode->i,newNode->j,n,newNode,data,frequencies);

	}
}

/*
	finds index where the greatest probability is located between i and j
*/
int findGreatestProbIndex(double frequencies [2045], int i,int j){
	double largestProb = 0.0;
	int largestProbIndex = 0;

	for(int f = i; f<=j; f++){
		if(frequencies[f]/2045 > largestProb ){
			largestProb = frequencies[f]/2045;
			largestProbIndex = f;
		}
	}	
	return largestProbIndex;
}





