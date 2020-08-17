/*
Name: Safwan Hossain
Date: 30/03/2020
*/

#include "funcPrototypes.h"
/*
parses the data_7.txt file calculates frequencies
create both root and main tables and searches for the key
*/
void optimalBSTDynamicProgramming(char* argv, char* userData){

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


		//create main and root table
		int n = addCount-1; //number of keys
		double mainTable[n+2][n+1]; //main Table
		int rootTable[n+2][n+1]; //root Table

		//initialize root table and mainTable
		for(int i=0;i<n+2;i++){
			for(int j =0;j<n+1;j++){
				rootTable[i][j]=-1;
				mainTable[i][j]=0;
			}
		}
		int j,i=0; //j = column; i = row
		for(j=0;j<n+1;j++){
			mainTable[i][j] = -1; //0th row of table empty (-1)
			rootTable[i][j] = -1; //0th row of table empty (-1)
		}

		//all diagonal starting from i=1
		// mainTable[1][0]....mainTable[n+1][n] = 0
		// rootTable[1][0]....rootTable[n+1][n] = -1
		for (i=1;i<n+2;i++){
			mainTable[i][i-1] = 0;
			rootTable[i][i-1] = -1; 
		}

		//all diagonal [1][1], [2][2], [3][3]....[n][n] = freq/2045
		// rootTable[1][1], [2][2], [3][3]....[n][n] = i
		for (i=1;i<n+2;i++){
			mainTable[i][i]= frequencies[i-1]/2045; //probability
			rootTable[i][i] = i; 
		}
		
		//fill rest of the values of main table diagonally
		i=1;
		j=2;
		int incrementer=1;
		double * costAndNode;
		do {
			costAndNode = calculateMainTableVal(i,j,n,mainTable,frequencies);
			mainTable[i][j] = costAndNode[0];
			rootTable[i][j] = costAndNode[1]; 

			if(j == n && i != 1){
				j = 2 + incrementer;
				incrementer++;
				i = 1;
			}else{
				i++;
				j++;
			}
		} while(i != 1 || j != n);

		costAndNode = calculateMainTableVal(i,j,n,mainTable,frequencies);
		mainTable[i][j] = costAndNode[0]; //last one
		rootTable[i][j] = costAndNode[1]; 

		TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
		root->data = data[rootTable[1][n]-1];
		root ->avgKeyComp = mainTable[1][n];
		root->i = 1;
		root->j = n;
		root = createTree(1,n,n,root, data, mainTable, rootTable);

		//search
		int found = -1;
		while(found == -1){
			if(root == NULL){
				printf("Not Found\n");
				found=0;
			}else if(strcmp(userData,root->data) == 0){
				printf("Compared with %s (%lf), found.\n", root->data,root->avgKeyComp);
				found = 0;
			}
			else if(strcmp(userData,root->data) < 0){
				printf("Compared with %s (%lf), go left subtree.\n", root->data,root->avgKeyComp);
				root=root->left;
			}
			else if(strcmp(userData,root->data) > 0){
				printf("Compared with %s (%lf), go right subtree.\n", root->data,root->avgKeyComp);
				root=root->right;
			}
		}

	}

}
/* creates the optimal BST using an array working like a stack */
TreeNode* createTree(int i, int j, int n, TreeNode*root, char data [2045][30], double mainTable[n+2][n+1], int rootTable[n+2][n+1]){

	TreeNode **stack = (TreeNode**)malloc(sizeof(TreeNode)*1000);
	TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));

	int s = 0;
	int l = 0;
	stack[s] = root; 
	while(s >= 0){
		node = stack[s];
		s--;
		i = node->i;
		j = node ->j;
		l = rootTable[i][j];
		if( l == j){ node->right =NULL;}
		if( l == i){ node->left =NULL;}
		if( l < j){//right tree
			TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
			newNode->data = data[rootTable[l+1][j]-1];
			newNode ->avgKeyComp = mainTable[l+1][j];
			newNode->i = l+1;
			newNode->j = node->j;
			node->right = newNode;
			s++;
			stack[s]=newNode;
		}
		if(i < l){//left tree
			TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
			newNode->data = data[rootTable[i][l-1]-1];
			newNode ->avgKeyComp = mainTable[i][l-1];
			newNode->i = node->i;
			newNode->j = l-1;
			node->left = newNode;
			s++;
			stack[s]=newNode;
		}

	}
	return root;
}


double* calculateMainTableVal(int i, int j, int n, double mainTable[n+2][n+1],double *frequencies){
	double* costAndNode = (double*)malloc(sizeof(double)*2);

	//i <= range <= j
	double cost[700] ={0};
	double probabilitySum=0;
	int k=0;
	for(int range=i; range <=j;range++){
		cost[k] = mainTable[i][range-1] + mainTable[range+1][j];
		k++;
		probabilitySum += frequencies[range-1]/2045; // -1 because frequency array index starts from 0
	}
	
	double minVal = cost[0];
	int nodeSelected=i;
	for(int s=0;s<j-i+1;s++){
		if(cost[s] <= minVal ){
			minVal = cost[s];
			nodeSelected=i+s; 
		}
	}
	
	costAndNode[0] = probabilitySum+minVal;
	costAndNode[1] = nodeSelected;
	return costAndNode;
}


