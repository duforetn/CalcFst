#include <stdio.h>
#include <stdlib.h>
#include "read_params.h"

int DataCounter(char *NameINPUT, int *nrow, int *ncol, char *format){

        FILE *INPUTFile;
        long long  nbbn = 0;
        long long nbsp = 0;
        long long res;
        int currentchar;
        int prevchar;
        if((INPUTFile = fopen(NameINPUT, "r")) == NULL){
                printf("Error, invalid input file\n");
                return 1;
        }
        currentchar = fgetc(INPUTFile);
        while(currentchar != EOF){
                if (currentchar == 10){
                        nbbn++;
                        if (prevchar != 32 && prevchar != '\t'){
                                nbsp++;
                        }
                }
                if ((currentchar == 32 || prevchar == '\t') && (prevchar != 32 || prevchar != '\t')) nbsp++;
                prevchar = currentchar;
                currentchar = fgetc(INPUTFile);
        }

        fclose(INPUTFile);
        if(!strcmp(format, "genotypes")){
                *nrow = (int)  nbbn;
                if(nbbn > 0){ *ncol = nbsp/nbbn; }
                else {*ncol = res;}
        }
        return 0;
}
int getNumberOfPopulation(int *POPs, int nIND){

        int i, j, count = 1;
        int *unique = malloc(sizeof(int)*nIND);
        *unique = POPs[0];
        for (i=1; i<nIND; i++){
                for (j=0; j<(count); j++){
                        if (POPs[i] == *(unique + j)) break;
                }
                if (j == count){
                        //unique + count = malloc(sizeof(float));
                        *(unique + count) = POPs[i];
                        //printf("nouveau unique: %f\n", *(unique + count));
                        count++;
                }
        }
        free(unique);
        return count;
}

void getPopSizes(int *PopSizes, int *POPs, int nIND, int nPOP){

                int i, p;
                for (p=0; p<nPOP; p++){
                        PopSizes[p] = 0;
                        for (i=0; i<nIND; i++){
                                if (POPs[i] == p + 1) PopSizes[p]++;
                        }
                }

                for (i=0; i<nPOP; i++){
                	printf("Size of Population %i: %d\n", i + 1, PopSizes[i]);
                }
}


void read_params(int argc, char *argv[], char **popfile, char **genofile, char **fstfile, int **POPs, int **PopSizes, int *nIND, int *nSNP, int *nPOP, int ploidy){
	
	int i, tmp, ind;
	int value;
        FILE *MyFILE;

        for (i=0; i<argc; i++){
                if (argv[i][0] == '-'){
                        switch(argv[i][1]){
                                case 'i':
                                        *genofile = strdup(argv[i + 1]);
                                        printf("Genotypes in file %s\n", *genofile);
                                        if(!DataCounter(*genofile, nSNP, nIND, "genotypes")){
						*nIND /= ploidy;
//                                                printf("%i snps typed on %i individuals\n", *nSNP, *nIND);

                                        } else { printf("ERROR: problem with the geno file\n");}
                                break;
				case 'p':
                                        *popfile  = strdup(argv[i + 1]);
					if((MyFILE = fopen(*popfile, "r")) == NULL){
				                printf("Error, invalid pop file\n");
				                break;
					}
                                        printf("Populations in file %s\n", *popfile);
					DataCounter(*popfile, &tmp, nIND, "genotypes");
					*POPs = malloc(sizeof(int)*(*nIND));
					ind = 0;
					fscanf(MyFILE, "%d", &value);
					while (ind<*nIND && value != EOF){
						(*POPs)[ind] = value;
						fscanf(MyFILE, "%d", &value);
						ind++;
					}
					*nPOP = getNumberOfPopulation(*POPs, *nIND);
					*PopSizes = malloc(sizeof(int)*(*nPOP));
					getPopSizes(*PopSizes, *POPs, *nIND, *nPOP);
                                break;
				case 'o':
					*fstfile  = strdup(argv[i + 1]);
				break;
			}
		}
	}
}

