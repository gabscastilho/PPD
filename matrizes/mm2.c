// Vesão com paralelização do segundo loop
// Paralelização da geração das matrizes
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

float **A, **B, **C;

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
	A = malloc(lin_a * sizeof(float*));
	B = malloc(lin_b * sizeof(float*));
	C = malloc(lin_c * sizeof(float*));

	for(int i = 0; i < lin_a; i++) A[i] = malloc(sizeof(float) * col_a);
	for(int i = 0; i < lin_b; i++) B[i] = malloc(sizeof(float) * col_b);
	for(int i = 0; i < lin_c; i++) C[i] = malloc(sizeof(float) * col_c);


	// Criando a seed a seed com base no tempo

 	unsigned int seed = time(NULL);

	// Fazendo o povoamento dos arrays de forma paralela
	// Fazendo o povoamento dos arrays de forma paralela
	#pragma omp parallel for
	for (i = 0; i < lin_a; i++)
		for (j = 0; j < col_a; j++)
			A[i][j] = (float)rand_r(&seed) / (float)RAND_MAX;

	#pragma omp parallel for
	for (i = 0; i < lin_b; i++)
		for (j = 0; j < col_b; j++)
			B[i][j] = (float)rand_r(&seed) / (float)RAND_MAX;
	// calculo da multiplicacao
 
	// Qual/quais loop(s) paralelizar? Vale a pena paralelizar todos?
	// Qual é o efeito de fazer um parallel for em cada um dos fors abaixo?
	// É necessários sincronizar alguma operação, garantindo exclusão mútua?
    
	for(i=0; i < lin_c; i++) 
    	#pragma omp parallel for private(k)
		for(j=0; j < col_c; j++) {
			int localSum = 0;		// Usando uma variável auxiliar local para evitar concorrência ao vetor
 
			for(k=0; k < col_a; k++) 
				localSum += A[i][k] * B[k][j];
			C[i][j] = localSum;	// Resgatando o valor da variável local
		}

	return(0);
}