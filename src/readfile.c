#include <stdlib.h>
#include <stdio.h>

// prints an error and exists when file isnt found 
void printerr (FILE *bf_file){
	if (bf_file == NULL){				// the file doesnt exist
		fprintf(stderr, "File doesn't exist\n");
		exit(EXIT_FAILURE);
	}
}

// returns the size of a file 
int filesize(char *filename){
	FILE *bf_file;			// brainfuck file pointer
	bf_file = fopen(filename, "r");		// opening the file in read mode
	printerr(bf_file);	
	fseek(bf_file,0,SEEK_END);		// putting the cursor at the end of the file 
	int size = ftell(bf_file);		// storing it in a variable to close the file
	fclose(bf_file);
	return (size);
}

// reads the file and load it in memory(heap)
char* loadfile(char *filename){
	char *file_content = (char *) malloc(filesize(filename) * sizeof(char));	// allocating size for the file content 
	// opening the file 
	FILE *bfcode;
	bfcode = fopen(filename, "r");				// opening bfcode in readmode
	// there is no need to a check here filesize() will do the job
	// malloc guard 
	if (file_content == NULL ){
		fprintf(stderr, "An error happened in memory allocation");
		exit(EXIT_FAILURE);
	}
	fread(file_content, filesize(filename), 1,bfcode);			// reading from the file into file_content
	fclose(bfcode);			// closing the file
	return (file_content);
}
