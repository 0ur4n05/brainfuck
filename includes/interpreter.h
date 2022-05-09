#ifndef INTERPRETER_H
#define INTERPRETER_H

void master_interpreter(char *filename);
void bfcore(char *bfcode, int* cfxindex);
extern unsigned char memblocks[30000];					// all of the memblocks are set to 0 
extern int mindex;				// memblocks index
extern int cfindex;				// code index

#endif
