#include "../includes/readfile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void loop(char *memcell, char *bfcode);

// extract the command that is inside the loop 
char *bfloop(int *index, char *bfcode){
	int i = *index;		
	int bfsize = 0;				// the size of the payload to mallocate more size for it 
	while (bfcode[i] != ']'){
		i++;
		bfsize++;
	}
	char *bfLoopCode = (char *) malloc(bfsize  * sizeof(char)); // +1 for the null terminator  
	// copy the code into 
	i = *index + 1;
	bfsize = 0;
	while (bfcode[i] != ']'){
		bfLoopCode[bfsize] = bfcode[i];
		bfsize++;
		i++;
	}
	bfLoopCode[bfsize] = '\0';			// terminating the string 
	// for some reason the allocated string have some traces of the file in it, idk why 
	*index += bfsize + 2;			// skipping the loop code 
	return (bfLoopCode);
}

// add one to the pointed value 
// called when the char + is detected
void plus(char *memcell){
	*memcell = *memcell + 1;				// incrementing the inside of the pointer by one 
}

// called when the char + is detected
// decremet the memcell by one 
void minus(char *memcell){
	*memcell = *memcell - 1;				// decremeting the inside of the pointer by one 
}
// function thar read code and executes it 
// the function is separated from master_interpreter to have the compatibility to have loops and execute 
// the code between the loops 
void bfcore(char *bfcode){
	char memblocks[30000] = {0};					// all of the memblocks are set to 0 
	int codesize = strlen(bfcode);			// used to read the bf code 

	// reading the file_content and executing the code 
	int i = 0;				// memblocks index
	int j = 0;				// bfcode index
	// reading an processing the code 
	while (j < codesize){
		// checking if the index has gone out of range
		if (i < 0 || i > 30000){
			printf("%d\n",i);
			fprintf(stderr, "RANGE ERROR\n");
			exit(EXIT_FAILURE);
		}
		switch (bfcode[j]){
			case '+':
				plus(&memblocks[i]);				// giving it the address of the memcell
				break;
			case '-':
				minus(&memblocks[i]);				// giving it the address of the memcell
				break;	
			// shifting 
			case '>':
				i++;
				break;
			case '<':
				i--;
				break;	
			case '.':
				putchar(memblocks[i]);				// printing the char where i is pointing 
				break;
			case ',':
				memblocks[i] = getchar();		// get char and store it in the memory cell 
				break;
			case '[':
				char *loopcode = bfloop(&j, bfcode) ;			// extracting the command inside the loop
				loop(&memblocks[i], loopcode);
				break;
			default :			// ignoring any char that isnt bf code  
				j = j;
		}	
		j++;
	}
}

// loop over a function 
// memcell : the current cell at the loop 
// bfcode : the code between []
void loop(char *memcell, char *bfcode){
	while (*memcell != 0){			// while the content of the cell doesnt equal 0
		printf("%c\n", *memcell);
		bfcore(bfcode);				// execute the code between the loop 	
	}
}

void master_interpreter(char *filename){
	char *file_content = loadfile(filename);		// the pure bfcode, without comments  
	bfcore(file_content);
	free(file_content);
}
