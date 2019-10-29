#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 100

void showMatrix(int matrix[N][N])
{
	for(int i=0; i<N ; i++)
	{
		for(int j=0; j<N; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void fill(int matrix[N][N])
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			matrix[i][j]=1;
		}
	}
}

void sum(int m1[N][N], int m2[N][N], int result[N][N])
{
	#pragma omp parallel
	#pragma omp for
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			result[i][j]=m1[i][j]+m2[i][j];
		}
	}
}


void multiply(int m1[N][N], int m2[N][N], int result[N][N])
{
	#pragma omp parallel
	#pragma omp for
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			result[i][j]=0;
			for(int k=0; k<N ; k++)
			{
				result[i][j] += m1[i][k]*m2[k][j];
			}
		}
	}
}



int main(int argc, char* argv[])
{
	int A[N][N],B[N][N],C[N][N],D[N][N],E[N][N],F[N][N],G[N][N],H[N][N];
	fill(A);
	fill(B);
	fill(C);
	fill(D);
	fill(E);
	fill(F);
	fill(G);
	fill(H);
	int mulAB[N][N];
	int mulCD[N][N];
	int mulEF[N][N];
	int mulGH[N][N];

	#pragma omp parallel
	{
	    #pragma omp sections
	    {
		#pragma omp section
		    multiply(A,B,mulAB);
		#pragma omp section
		    multiply(C,D,mulCD);
		#pragma omp section
		    multiply(E,F,mulEF);
		#pragma omp section
		    multiply(G,H,mulGH);
	    }
	}
	int mulABCD[N][N];
	int sumEFWithGH[N][N];

	#pragma omp parallel
	{
		#pragma omp sections
		{
			#pragma omp section
			multiply(mulAB,mulCD,mulABCD);
			#pragma omp section
			sum(mulEF,mulGH,sumEFWithGH);
		}
	}
	showMatrix(mulABCD);
	showMatrix(sumEFWithGH);
	return 0;
}
