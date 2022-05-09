#include <stdio.h>
#include <stdlib.h>
#include "../includes/interpreter.h"
#include <unistd.h> 

// just get the fucking arguments al call functions 
int main(int argc, char **argv){
	if (argc < 2 || argc > 3){
		puts("Usage : ./bf -c <BFCODE>\n    or: ./bf <FILENAME>");
		exit(EXIT_FAILURE);
	}
	int opt;
	while((opt = getopt(argc, argv, ":c:")) != -1) { 
		switch(opt){
			case 'c':
				bfcore(optarg, &cfindex);
				exit(EXIT_SUCCESS);
				break;
            case '?':
                fprintf(stderr, "Invalid option\n");
                exit(EXIT_FAILURE);
			default : ;
		}
	}
	master_interpreter(argv[1]);
}
