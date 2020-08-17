/*
*/
#include "funcProtoypes.h"

/*
Brute force anagram algorithm
shows time taken to search and sort sepeartely
Displays the anagrams, their index and number of anagrams excluding the string itself
*/
void bruteForce(char **argv,char *userData){

	int anagramData[30000];
	char anagramWords[30000][15];
	FILE *fp = fopen(argv[1],"r");

	if (fopen(argv[1],"r") != NULL) {
		int i = 0;
		while (!feof (fp)){ 
			char word[15]; 
			fscanf (fp, "%d", &anagramData[i]); 
			sprintf(word, "%d", anagramData[i]);
			strcpy(anagramWords[i],word);
			i++; 
		}

	}
	fclose (fp); 


    struct timeb startTime;
    struct timeb endTime;
    float delta;

	ftime(&startTime);

	int numOfEachDigitUser[10]={0};
	int numOfEachDigitDataFile[10]={0};
	int AnagramCounter = 0;

	for(int j=0;j<10;j++){
		numOfEachDigitUser[j] = counter(userData,j+'0');
		//printf("User Data\nNumber: %d  Count: %d\n",j,numOfEachDigitUser[j]);
	}

	for(int i=0;i<30000;i++){
		if(strlen(userData) == strlen(anagramWords[i])) {
			for(int j=0;j<10;j++){
				numOfEachDigitDataFile[j] = counter(anagramWords[i],j+'0');
			}

			if(AngramOrNot(numOfEachDigitUser,numOfEachDigitDataFile) == 0){

				if( strcmp(userData,anagramWords[i]) != 0){ //get rid of this if not needed
					AnagramCounter++;
					printf("Index: %d ---> Anagram of %s\n",i,anagramWords[i]);
				}
				
			}
		}

	}
	ftime(&endTime);
	delta = (endTime.time - startTime.time)*1000 + (endTime.millitm - startTime.millitm);
	printf("Number of Anagrams excluding string itself: %d\n",AnagramCounter);
	printf("Time taken: %f ms\n",delta);
}

/*Counts how many of c are in str*/
int counter(char *str,char c){
	int count=0;
	for(int i=0;i<(int)strlen(str);i++){
		if(str[i] == c){
			count++;
		}
	}

	return count;
}

int AngramOrNot(int *numOfEachDigitUser,int *numOfEachDigitDataFile){
	for(int i=0;i<10;i++){
		if(numOfEachDigitUser[i] !=  numOfEachDigitDataFile[i]){
			return 1;//false
		}
	}
	return 0;//true
}
