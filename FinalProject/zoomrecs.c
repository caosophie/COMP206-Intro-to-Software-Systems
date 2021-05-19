#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "zoomrecs.h"

struct ZoomRecord *head = NULL;

//add in front
void addnode(char *email, char *name, char *lab, int min){
        struct ZoomRecord *temp = (struct ZoomRecord*)malloc(sizeof(struct ZoomRecord));

        if (temp == NULL){
                printf("Error! program ran out of memory");
                exit(1);
        }

        strcpy(temp->email, strdup(email));
        strcpy(temp->name, strdup(name));
	
	char letter = 'A';

	for (int i = 0; i < 9; ++i){
		if (*lab == letter) {temp->durations[i] += min; break;}
		else letter = letter  + 1;
	}	

        temp->next = head;
        head = temp;
        return;
}

//add after specific node
void addafternode(struct ZoomRecord *prevNode, char *email, char *name, char *lab, int min){
        struct ZoomRecord *temp = (struct ZoomRecord*)malloc(sizeof(struct ZoomRecord));

        if (temp == NULL){
                printf("Error! program ran out of memory");
                exit(1);
        }

        strcpy(temp->email, strdup(email));
        strcpy(temp->name, strdup(name));

        char letter = 'A';

        for (int i = 0; i < 9; ++i){
                if (*lab == letter) {temp->durations[i] += min; break;}
                else letter = letter  + 1;
        }

        temp->next = prevNode->next;
        prevNode->next = temp;
        
	return;
}

void addZoomRecord(char *token, char *token1, char *token2, int min){
	struct ZoomRecord *temp = head;
        char boolean[] = "F";
	//check if person is already in the linked list -> yes, return true. no, return false
        while (temp != NULL)
        {
                if (strcmp(temp->email, token) == 0){
                        strcpy(boolean, "T");
                        char letter = 'A';

		        for (int i = 0; i < 9; ++i){
                		if (*token2 == letter) {temp->durations[i] += min; break;}
                		else letter = letter  + 1;
        		}
			break;
                }
                temp = temp->next;
        }

	int added = 0;

        if (strcmp(boolean, "T") == 0);
        else {
                struct ZoomRecord *ptr = head;
                struct ZoomRecord *prev = head;

                char c = token[0];
	
                if (head == NULL || c < head->email[0]) addnode(token,token1,token2,min); //if linked list is empty or first letter of email is smaller than head->email, add at the front of list
                else {
                        while (ptr != NULL){ //if no, traverse the list to find good place
                                if (ptr->email[0] > c){ //if person in list comes right after current student, then add curr student right before
                                        addafternode(prev, token, token1, token2, min);
                                        ptr = NULL;
					added = 1;
                                        break;
                                } else if (ptr->email[0] == c) {
					//if the first letters are the same, check 2nd letter, 3rd, and etc.
                                        for (int i = 1; ptr->email[i] != '\0'; ++i){
                                                if (ptr->email[i] > token[i]){
                                                        addafternode(prev, token, token1, token2, min);
							ptr = NULL;
							added = 1;
                                                        break;
                                                } else if (ptr->email[i] == token[i]);
                                                else break;
                                        }
					//if we haven't added yet, continue traversing list
					if (added == 0) {
						prev = ptr;
						ptr = ptr->next;
					}
                                } else {
					prev = ptr;
				 	ptr = ptr->next;	
				
				}
                        }
			//for cases where we've reached the end of the list and student hasn't been added yet
                        if (added == 0) addafternode(prev, token, token1, token2, min);
                }
        }

}

void generateAttendance(FILE *outputfile){
        int count = 0;
        float avg;
        struct ZoomRecord *ptr = head;
        struct ZoomRecord *last;

        if (ptr->email == NULL) {return;} //if there is no valid output, break out

        while  (ptr != NULL){
		//check if times for lab is valid, if yes, increase count
                for (int i = 0; i < 9; i++){
                        if (ptr->durations[i] >= 45) {count++;}
                }

                avg = (count/9.0)*100;

                fprintf(outputfile, "%s, %s, %d, %d, %d, %d, %d, %d, %d, %d, %d, %2.2f\n", ptr->email, ptr->name, ptr->durations[0], ptr->durations[1], ptr->durations[2], ptr->durations[3], ptr->durations[4], ptr->durations[5], ptr->durations[6], ptr->durations[7], ptr->durations[8], avg);

                count = 0;

                ptr = ptr->next;
        }

        last = ptr;

        return;
}

//free memory
void freelist(){
	struct ZoomRecord *ptr = head;
	struct ZoomRecord *f = head;

	while (ptr != NULL){
		ptr = ptr->next;
		free(f);
		f = ptr;
	}
}
