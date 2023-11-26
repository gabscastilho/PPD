// Vesão com paralelização do primeiro loop
/*
** PPD / DC/UFSCar - Helio
** Programa : multiplicacao de matrizes
** Objetivo: paralelizacao om OpenMP
*/

#include <math.h>
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>

float *A, *B, *C;

int
main(int argc, char *argv[])
{
	int lin_a,col_a,lin_b,col_b,lin_c,col_c;
	int i,j,k;

	printf("Linhas A: ");   scanf("%d",&lin_a);
	printf("Colunas A / Linhas B: "); scanf("%d",&col_a);
	lin_b = col_a;
	printf("Colunas B: ");  scanf("%d",&col_b);
	printf("\n");
	lin_c = lin_a;
	col_c = col_b;

	// Alocacao dinâmica das matrizes, com linhas em sequência 
	A = (float *) malloc ( lin_a * col_a * sizeof(float) );
	B = (float *) malloc ( lin_b * col_b * sizeof(float) );
	C = (float *) malloc ( lin_c * col_c * sizeof(float) );

 	// Atribucao de valores iniciais às matrizes 
 	srand(time(NULL));

	// Opa! Vai gerar valores aleatórios em paralelo?
	// Talvez seja o caso de usar rand_r() ao invés de rand()...
  
	for(i=0; i < lin_a * col_a; i++) 
		A[i]=(float)rand() / (float)RAND_MAX; 

	for(i=0; i < lin_b * col_b; i++) 
		B[i]=(float)rand() / (float)RAND_MAX; 

	// calculo da multiplicacao
 
	// Qual/quais loop(s) paralelizar? Vale a pena paralelizar todos?
	// Qual é o efeito de fazer um parallel for em cada um dos fors abaixo?
	// É necessários sincronizar alguma operação, garantindo exclusão mútua?
    
    #pragma omp parallel for private(j,k)
	for(i=0; i < lin_c; i++) 

		for(j=0; j < col_c; j++) {

			// pode ser útil usar uma variável auxiliar para os cálculos
			C[i*col_c+j]=0;
 
			for(k=0; k < col_a; k++) 
				C[i*col_c+j] = C[i*col_c+j] + A[i*col_a+k] * B[k*col_b+j];
       
       // ser usou variável auxiliar, atribui-se seu valor à C[i][j]
		}

	return(0);
}