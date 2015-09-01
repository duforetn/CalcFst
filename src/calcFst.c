#include <stdio.h>
#include <stdlib.h>
#include "read_params.h"
#include "get_geno.h"
#include "Fst_geno.h"

int main(int argc, char *argv[]){

	char *popfile = malloc(sizeof(char)*256);
	char *genofile = malloc(sizeof(char)*256);
	char *fstfile = malloc(sizeof(char)*256);
	int nSNP, nIND, nPOP, ploidy = 2, snp = 0, i;
	int *POPs;
	int *PopSizes; 
	double af;

	if (!(strcmp(argv[1], "HAPLO"))) ploidy = 1;
	if (!(strcmp(argv[1], "DIPLO"))) ploidy = 2;
	read_params(argc, argv, &popfile, &genofile, &fstfile, &POPs, &PopSizes, &nIND, &nSNP, &nPOP, ploidy);

        double *FstWC = calloc(nSNP, sizeof(double));
        double *Geno;
	FILE *MyGenoFile = fopen(genofile, "r");
	Geno = calloc(nIND, sizeof(double));

	for (snp=0; snp<nSNP; snp++){
		af = get_geno(MyGenoFile, Geno, nIND, ploidy);
		if (af > 0 && af < 1){FstWC[snp] = Fst_geno(Geno, POPs, PopSizes, nIND, nPOP);}
		else {FstWC[snp] = 0;}
		if(FstWC[snp] > 1.5 || FstWC[snp] < -.5) FstWC[snp] = 0;
	}

        if(!strcmp(fstfile, "")) fstfile = "Fsts";
	FILE *MyFstFile = fopen(fstfile, "w");
	for (snp=0; snp<nSNP; snp++) fprintf(MyFstFile, "%g\n", FstWC[snp]);

	free(FstWC);

	return 0;

}
