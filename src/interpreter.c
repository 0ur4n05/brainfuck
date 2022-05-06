#include "../includes/readfile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

// shift the pointer left by substracting one 
void shiftleft(int *index){
	*index = *index - 1;
}

// shift the pointer right by adding one 
void shiftright(int *index){
	*index = *index + 1;
}

void master_interpreter(char *filename){
	char *file_content = loadfile(filename);		// the pure bfcode, without comments  
	int codesize = strlen(file_content);			// used to read the bf code 
	char memblocks[30000] = {0};					// all of the memblocks are set to 0 

	// reading the file_content and executing the code 
	int i = 0;				// memblocks index
	int j = 0;				// bfcode index
	// reading an processing the code 
	while (j < codesize){
		// checking if the index has gone out of range
		if (i < 0){
			fprintf(stderr, "RANGE ERROR\n");
			exit(EXIT_FAILURE);
		}
		switch (file_content[j]){
			case '+':
				plus(&memblocks[i]);				// giving it the address of the memcell
				break;
			case '-':
				minus(&memblocks[i]);				// giving it the address of the memcell
				break;	
			// shifting 
			case '>':
				shiftright(&i);
				break;
			case '<':
				shiftleft(&i);
				break;	
			case '.':
				putchar(memblocks[i]);				// printing the char where i is pointing 
				break;
			case ',':
				memblocks[i] = getchar();		// get char and store it in the memory cell 
				break;
			default :			// ignoring any char that isnt bf code  
				j = j;
		}	
		j++;
	}
	free(file_content);
}
