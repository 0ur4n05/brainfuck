#include <stdio.h>
#ifndef READFILE_H
#define READFILE_H

void printerr (FILE *bf_file);
int filesize(char *filename);
void pureread(char *container, char* filename);
char* loadfile(char *filename);

#endif 
