#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

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
	#pragma omp parallel
	#pragma omp for private(x) reduction(+:integral_local)
        for( int j=1; j<=n; j++)
        {
                x = a + j*h;
                integral_local += f(x);
        }
	integral+=integral_local;
        integral *= h;
	printf("%f\n",integral);
	return 0;
}
