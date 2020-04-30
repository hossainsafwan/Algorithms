/*
Assignment 3
*/
#include "funcProtoypes.h"
int patternShift=0;

void horspoolAlgorithm(char **argv,char *userData) {
	int table [256] = {-1};//ascii table format

	int m = (int)(strlen(userData));

	createTable(userData,table);

    struct timeb startTime;
    struct timeb endTime;
    float delta;

	ftime(&startTime);

	FILE *fp = fopen(argv[2],"r");
	char readLine[512];
	int i = m-1;
	int matches=0;
	if (fopen(argv[2],"r") != NULL) {

	while(fgets(readLine,512,fp) != NULL) {
			matches += horspoolMatching( userData, readLine, i,m,table);
	}
		
	}
	ftime(&endTime);
	delta = (endTime.time - startTime.time)*1000 + (endTime.millitm - startTime.millitm);
	printf("\nHorspool\n");
	printf("Time taken: %f ms\n",delta);
	printf("Number of Matches %d\n",matches);
	printf("Number of Pattern Shifts: %d\n",patternShift);
	patternShift=0;
	fclose (fp); 
	
}

int horspoolMatching(char * userData, char *readLine, int i,int m,int table[256]){

	int numOfMatches=0;

	while(i <= (int)strlen(readLine)-1){
		int k = 0;
		while(k <= m-1 && userData[m-1-k] == readLine[i-k]){
			k++;
		}
		if(k == m){
			numOfMatches++;
			i = i + m +1;//index where match was found
		} else{
			//num of pattern shifts
			while((int)readLine[i] < 0 || (int)readLine[i] > 255) { //increment when i is at special character
				i++;
			}
			i = i + table[(int)readLine[i]]; 
			patternShift++;

		}				
	}
	return numOfMatches;

}

void createTable(char *userData, int table[256]) {

	//fill table with max shift values
	for(int i=0;i <= 256-1; i++){
		table[i] = (int)(strlen(userData));	
	}
	//fill shift values in table for all the characters in userData
	for(int j=0; j <=(int)strlen(userData)-2; j++) {
		table[(int)(userData[j])] = (int)strlen(userData) - 1 - j;
	}
}