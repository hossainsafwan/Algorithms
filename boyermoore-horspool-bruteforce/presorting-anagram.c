/*
*/
#include "funcProtoypes.h"
/*
Anagram Algorithm with presorting at first 
shows time taken to search and sort sepeartely
Displays the anagrams, their index and number of anagrams excluding the string itself
*/
void presorting(char **argv,char *userData){

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
	char anagramSortedData[30000][15];

	for(int i=0;i<30000;i++){
		for(int j=0;j<15;j++){
			anagramSortedData[i][j]=anagramWords[i][j];
		}
	}

	//bubble sort
	for(int i =0;i<30000;i++){

		for(int j=0;j<(int)(strlen(anagramSortedData[i]))-1;j++){
			
			for(int k=0;k<(int)(strlen(anagramSortedData[i]))-j-1;k++) {
				if(anagramSortedData[i][k] > anagramSortedData[i][k+1]) {
					char temp = anagramSortedData[i][k];
					anagramSortedData[i][k] = anagramSortedData[i][k+1];
					anagramSortedData[i][k+1] = temp;

				}
			}

		}
	}
	char UserDataCopy[15];
	strcpy(UserDataCopy,userData);

	//sort user data
	for(int j=0;j<(int)(strlen(userData))-1;j++){
		for(int k=0;k<(int)(strlen(userData))-j-1;k++) {
			if(userData[k] > userData[k+1]) {
				char temp = userData[k];
				userData[k] = userData[k+1];
				userData[k+1] = temp;
			}
		}

	}

	ftime(&endTime);
	delta = (endTime.time - startTime.time)*1000 + (endTime.millitm - startTime.millitm);

  	float delta2;
	ftime(&startTime);
	//check
	int anagramCount=0;
	int allequal = 0;
		for(int i=0;i<30000;i++){
			if((int)(strlen(userData)) == (int)(strlen(anagramSortedData[i]))){
				for(int j=0;j<(int)(strlen(anagramSortedData[i]));j++){
					if(anagramSortedData[i][j] != userData[j]){
						allequal=1;
						j=(int)(strlen(anagramSortedData[i]))+1;
					}
				}
				if(allequal == 0){
					if(strcmp(UserDataCopy,anagramWords[i]) != 0){
						anagramCount++;
						printf("Index: %d ----> Anagram: %s\n",i, anagramWords[i]);
					}

				}
				allequal=0;
			}

		}
	ftime(&endTime);
	delta2= (endTime.time - startTime.time)*1000 + (endTime.millitm - startTime.millitm);
	printf("Number of Anagrams excluding string itself: %d\n",anagramCount);
	printf("Sorting Time taken: %f ms\n",delta);
	printf("Search Time taken: %f ms\n",delta2);

}