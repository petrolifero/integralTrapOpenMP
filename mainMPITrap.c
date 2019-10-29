#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define NUMBER_OF_TRAP 1024

float f(float x)
{
	return x*x;
}

float calcula(float local_a, float local_b,int local_n, float h)
{
        float integral;
        float x, i;
        integral = ( f(local_a) + f(local_b) ) /2.0;
        x = local_a;
        for( i=1; i<=local_n; i++)
        {
                x += h;
                integral += f(x);
        }
        integral *= h;
        return integral;
}


int main(int argc, char* argv[])
{
	float a=0, b=1.0; // intervalo a calcular
	int n=2048; // número de trapezóides
	float h; // base do trapezóide
	float total=0; // integral total

	h = (b-a) / n;
	float integral,integral_local=0,intern_integral=0;
        float x, i;
        integral = ( f(a) + f(b) ) /2.0;
        x = a;
	MPI_Init(&argc,&argv);
	int numOfProcessors;
	MPI_Comm_size(MPI_COMM_WORLD, &numOfProcessors);
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	int trapByProcess = n/numOfProcessors;
	int min = my_rank*trapByProcess;
	int max;
	if(my_rank == numOfProcessors-1)
	{
		max=n;
	}
	else
	{
		max=(my_rank+1)*trapByProcess-1;
	}
        for( int j=min; j<=max; j++)
        {
                x = a + j*h;
                integral_local += f(x);
        }
	MPI_Reduce(&integral_local,&integral,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
	if(my_rank == 0)
	{
	        integral *= h;
		printf("%f\n",integral);
	}
	MPI_Finalize();
	return 0;
}
