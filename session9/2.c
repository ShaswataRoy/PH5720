#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<gsl/gsl_linalg.h>

double T[100][100];
gsl_vector *x;

void PDE(double alpha)
{
	gsl_vector * b = gsl_vector_alloc(100);
	gsl_vector * x = gsl_vector_alloc(100);
	gsl_vector * diag = gsl_vector_alloc(100);
	gsl_vector * e = gsl_vector_alloc(99);

	for(int i=0;i<100;i++)
	{
		gsl_vector_set(diag,i,1-2*alpha);
		gsl_vector_set(b,i,T[i][0]);
		if(i!=(99))
		{
			gsl_vector_set(e,i,alpha);
		}
	}

	for(int i=0;i<100;i++)
	{
		gsl_linalg_solve_symm_tridiag(diag,e,b,x);
		for(int j=0;j<100;j++)
		{
			T[j][i] = gsl_vector_get(x,j);

			gsl_vector_set(b,j,T[j][i]);
		}
	}
	gsl_vector_free(x);
	gsl_vector_free(b);
	gsl_vector_free(diag);
	gsl_vector_free(e);
}

int main()
{
	FILE * fp;
	fp = fopen("diffusion.dat","w");
	double alpha = 0.1;
	for(int i=0;i<100;i++)
	{
		T[i][0]=100;
	}
	T[0][0]=0;T[99][0]=0;

	PDE(alpha);

	for(int i=0;i<100;i++)
	{
		for(int j=0;j<100;j++)
		{
			fprintf(fp," %.15lf \t %.15lf \t %.15lf \n", (double)j, (double)i/100000, T[i][j]);
		}

		fprintf(fp, "\n");

	}

	return(0);


}
