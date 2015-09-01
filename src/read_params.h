#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int DataCounter(char *NameINPUT, int *nrow, int *ncol, char *format);

int getNumberOfPopulation(int *POPs, int nIND);

void getPopSizes(int *PopSizes, int *POPs, int nIND, int nPOP);

void read_params(int argc, char *argv[], char **popfile, char **genofile, char **fstfile, int **POPs, int **PopSizes, int *nIND, int *nSNP, int *nPOP, int ploidy);
