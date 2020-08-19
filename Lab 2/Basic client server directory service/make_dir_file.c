#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

typedef struct datum{
	int code;
	char matched_name[100];
} database;

int main (){ 
	FILE *fptr;
	if ((fptr = fopen("directory.txt","w")) == NULL){
		printf("Error opening file");
		exit (1); 
	} 

	char ch;
	database record;
	do{
		printf("\nEnter Address Code: ");
		scanf("%d",&record.code);

        printf("Enter Name: ");
        scanf("%s",record.matched_name);

        fwrite (&record, sizeof(database), 1, fptr);
		printf("\nDo you wish to add another entry (y/n): ");
		scanf(" %c",&ch);
	}while(ch=='y' || ch=='Y');
 
	fclose (fptr);
	return 0; 
} 
