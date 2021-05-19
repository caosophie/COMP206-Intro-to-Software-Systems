#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "zoomrecs.h"

int main(int argc, char *argv[]){
	FILE *f = fopen(argv[1], "r");
	FILE *output = fopen(argv[2], "w");

	if (f == NULL){
                printf("Error! Unable to open the input file %s\n", argv[1]);
                exit(1);
	}

        char str[200];
        const char s[2] = ",";

        fgets(str, sizeof(str), f);

        while (fgets(str, sizeof(str), f)){
		char *token, *token1, *token2, *token3;
                //email
                token = strtok(str, s);
                //name
                token1 = strtok(NULL, "," );
                //lab
                token2 = strtok(NULL, s);
                //time
                token3 = strtok(NULL, s);

                int minute = atoi(token3);
		//printf("%s, %s, %s, %s\n", token, token1, token2, token3);

		addZoomRecord(token, token1, token2, minute);
	}

	fclose(f);
	fprintf(output, "%s\n", "User Email,Name (Original Name),A,B,C,D,E,F,G,H,I,Attendance (Percentage)");
	generateAttendance(output);

	freelist();
	return 0;
}
