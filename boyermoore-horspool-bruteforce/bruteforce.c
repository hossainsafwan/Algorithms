/*
String Search via Brute Force Method
*/
#include "funcProtoypes.h"
 /*
Brute force string search
 */
 void bruteForceStringSearch(char **argv,char *userData) {
 	
	char readLine[512];
	int patternShifts=0;
	int j=0; //character matches
	int matchCount=0;
	FILE *fp = fopen(argv[2],"r");

	struct timeb startTime;
    struct timeb endTime;
    float delta;

	ftime(&startTime);

	if (fopen(argv[2],"r") != NULL) {

		while(fgets(readLine,512,fp) != NULL) {
			
			for(int i=0; i<(int)strlen(readLine); i++){

				if(j == (int)strlen(userData)){
					matchCount++;
					j=0;
				}

				if( readLine[i] >= 0 && readLine[i] <=255 ) { //only special characters

					if(userData[j] == readLine[i]){
						j++;
					}else{
						j = 0;
					}
				} else {
					j=0;
				}
				patternShifts++;
			}
		}
 	} else {
 		printf("Wrong file as input\n");
 	}

 	ftime(&endTime);
	delta = (endTime.time - startTime.time)*1000 + (endTime.millitm - startTime.millitm);
	printf("\nBrute Force\n");
	printf("Time taken: %f ms\n",delta);
	printf("Number of Matches %d\n",matchCount);
	printf("Number of Pattern Shifts: %d\n",patternShifts);
	fclose (fp); 
}