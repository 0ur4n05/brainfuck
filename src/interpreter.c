#include "../includes/readfile.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// loop range erros

void loop(char *memcell, char *bfcode);
char memblocks[30000] = {0};					// all of the memblocks are set to 0 
int mindex = 0;				// memblocks index
int cfindex = 0;				// code index

// extract the command that is inside the loop 
char *bfloop(char *bfcode){
	int i = cfindex;		
	int bfsize = 0;				// the size of the payload to mallocate more size for it 
	while (bfcode[i] != ']'){
		i++;
		bfsize++;
	}
	char *bfLoopCode = (char *) malloc(bfsize  * sizeof(char)); // +1 for the null terminator  
	// copy the code into 
	i = cfindex + 1;
	bfsize = 0;
	while (bfcode[i] != ']'){
		bfLoopCode[bfsize] = bfcode[i];
		bfsize++;
		i++;
	}
	bfLoopCode[bfsize] = '\0';			// terminating the string 
	// for some reason the allocated string have some traces of the file in it, idk why 
	cfindex += bfsize + 2;			// skipping the loop code 
	return (bfLoopCode);
}

// function thar read code and executes it 
// the function is separated from master_interpreter to have the compatibility to have loops and execute 
// the code between the loops 
void bfcore(char *bfcode){
	int codesize = strlen(bfcode);			// used to read the bf code 
	// reading the file_content and executing the code 
	// reading an processing the code 
	while (cfindex < codesize){
		// checking if the index has gone out of range
		if (mindex < 0 || mindex  > 30000){
			fprintf(stderr, "RANGE ERROR\n");
			exit(EXIT_FAILURE);
		}
		switch (bfcode[cfindex]){
			case '+':
				memblocks[mindex]++;
				break;
			case '-':
				memblocks[mindex]--;
				break;	
			// shifting 
			case '>':
				mindex++;
				break;
			case '<':
				mindex--;
				break;	
			case '.':
				putchar(memblocks[mindex]);				// printing the char where i is pointing 
				break;
			case ',':
				memblocks[mindex] = getchar();		// get char and store it in the memory cell 
				break;
			case '[':
				char *loopcode = bfloop(bfcode) ;			// extracting the command inside the loop
				loop(&memblocks[mindex], loopcode);
				break;
			default :			// ignoring any char that isnt bf code  
				cfindex = cfindex;
		}	
		cfindex++;
	}
}

// loop over a function 
// memcell : the current cell at the loop 
// bfcode : the code between []
void loop(char *memcell, char *bfcode){
	while (*memcell != 0){			// while the content of the cell doesnt equal 0
		bfcore(bfcode);				// execute the code between the loop 	
	}
}

void master_interpreter(char *filename){
	char *file_content = loadfile(filename);		// the pure bfcode, without comments  

	bfcore(file_content);
	free(file_content);
}
