/*
Assignment 3
*/
#include "funcProtoypes.h"

void boyerMooreAlgorithm (char **argv, char *userData){
	int tableBoyerMoore[256];
	int m,lineLen,i,j;
	int matches = 0;
	int patternShift=0;
	char line[512];

    struct timeb startTime;
    struct timeb endTime;
    float delta;
	
	FILE *fp = fopen(argv[2],"r");

	m = strlen(userData);
	
	createTableBoyerMoore(userData, m, tableBoyerMoore);
	ftime(&startTime);

	while (fgets(line, 512, fp) != NULL){
		lineLen = strlen(line);
		i =0;
		    while(i <= (lineLen - m)){
		        j = m-1;
		        while((j >= 0) && (userData[j] == line[i+j])){
					j--;						
				}
			        
		        if (j < 0){
		            matches++;
		            if (i+m < lineLen){
		            	i = i + m-tableBoyerMoore[(int)line[i+m]]; 
		            	patternShift++;
		            }
		            else{
		            	i = 1;
		            }
		        }			 
		        else{
		            i = i + findMax(1, j-tableBoyerMoore[(int)line[i+j]]);
		            patternShift++;
		        }
		        
		    }
	}
	ftime(&endTime);
	delta = (endTime.time - startTime.time)*1000 + (endTime.millitm - startTime.millitm);
	printf("\nBoyer Moore\n");
	printf("Time taken: %f ms\n",delta);
	printf("Number of Matches %d\n",matches);
	printf("Number of Pattern Shifts: %d\n",patternShift);
	fclose (fp); 

}

int findMax (int a, int b){
	if (a > b){
		return a;
	}
	return b;
}
void createTableBoyerMoore( char *str, int size, int tableBoyerMoore[256]){
    int j;
    for (int i = 0; i < 256; i++){
        tableBoyerMoore[i] = -1;
	} 
 
    for (j = 0; j < size; j++){
        tableBoyerMoore[(int)str[j]] = j;
    }
}

