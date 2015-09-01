#include <stdio.h>
#include <stdlib.h>
#define NA 9

double get_geno(FILE *MyGenoFile, double *Geno, int nIND, int ploidy){

        float value, value2;
        int ind = 0, i;
	double res = 0;
	while(ind < nIND){
        	if(fscanf(MyGenoFile, "%g", &value) != EOF){
	                if (ploidy == 2) Geno[ind] = (double) value;
			if (ploidy == 1){
				Geno[ind] = (double) value;
				fscanf(MyGenoFile, "%g", &value2);
				Geno[ind] += (double) value2;
				if(Geno[ind] >= NA) Geno[ind] = NA;
			}
			res += (double) Geno[ind]/2.0;
                }
		ind++;
	}

	return (double)	res/nIND;

}

