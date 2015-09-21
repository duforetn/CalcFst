#include <stdio.h>
#include <stdlib.h>
#include "Fst_geno.h"

double Fst_geno(double *Geno, int *POPs, int *PopSizes, int nIND, int nPOP){

	double n_bar = 0, n_c = 0;
	double *PopFreqs = calloc(nPOP, sizeof(double));
	double *PopHet = calloc(nPOP, sizeof(double));
	double p_bar = 0;
	double h_bar = 0;
	double s2 = 0;
	int i, p;
	
	for (p=0; p<nPOP; p++){
		n_bar += PopSizes[p]/nPOP;
		for (i=0; i<nIND; i++){
			if (POPs[i] == p + 1) PopFreqs[p] += Geno[i]/2.0;
			if (POPs[i] == p + 1 && Geno[i] == 1) PopHet[p]++;
		}
		PopFreqs[p] /= PopSizes[p];
		PopHet[p] /= PopSizes[p];
	}

	for (p=0; p<nPOP; p++){
		p_bar += PopSizes[p]*PopFreqs[p]/(n_bar*nPOP);
		h_bar += PopSizes[p]*PopHet[p]/(n_bar*nPOP);
	}
	
	n_c = nPOP*n_bar;
	for (p=0; p<nPOP; p++) n_c -= (PopSizes[p]*PopSizes[p]/(nPOP*n_bar));
	n_c /= nPOP - 1;

        for (p=0; p<nPOP; p++){
		s2 += PopSizes[p]*(PopFreqs[p] - p_bar)*(PopFreqs[p] - p_bar)/((nPOP - 1)*n_bar);
	}

h_bar = 0;
	double a = (n_bar/n_c)*(s2 - 1.0/(n_bar - 1.0)*(p_bar*(1.0 - p_bar) - s2*(nPOP - 1)/(nPOP) - h_bar/4.0));
	double b = (n_bar/(n_bar - 1.0))*(p_bar*(1.0 - p_bar) - ((nPOP - 1.0)/nPOP)*s2 - h_bar*(2*n_bar - 1)/(4*n_bar));
	double c = h_bar/2.0;

	return a;

}
