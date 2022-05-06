#include <stdio.h>
#include <stdlib.h>
#include "../includes/interpreter.h"

// just get the fucking arguments al call functions 
int main(int argc, char **argv){
	if (argc < 2){
		printf("Usage : ./bf <FILENAME>\n");
		exit(EXIT_FAILURE);
	}
	master_interpreter(argv[1]);
}
