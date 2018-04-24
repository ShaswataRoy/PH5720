#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <gsl/gsl_linalg.h>

gsl_matrix_view A;
gsl_vector_view B;
gsl_vector *x;
gsl_vector *xt;
double h;
FILE *fp;

void init_matrices_LU(const int N,double (*func)(double))
{
	double a_data[N*N];

	double b_data[N];

	h = 1.0/(N+1);

	for(int i=0;i<N;i++)
	{
		for(int j=0;j<N;j++)
		{
			if(i==j)
				a_data[N*i+j]=2;
			else if(abs(i-j)==1)
				a_data[N*i+j]=-1;
			else
				a_data[N*i+j]=0;
		}
		b_data[i] = h*h*((*func)(i*h+h));
	}

	A = gsl_matrix_view_array (a_data, N, N);

	B = gsl_vector_view_array (b_data, N);

	x = gsl_vector_alloc (N);

  	int s;

  	gsl_permutation * p = gsl_permutation_alloc (N);

  	gsl_linalg_LU_decomp (&A.matrix, p, &s);

  	gsl_linalg_LU_solve (&A.matrix, p, &B.vector, x);

 	gsl_permutation_free (p);
}


void init_matrices_TD(const int N,double (*func)(double))
{
	double b[N];
	double diag[N];
	double e[N-1];
	h = 1.0/(N+1);

	xt = gsl_vector_alloc (N);


	for(int i=0;i<N;i++)
	{
		b[i] = h*h*((*func)(i*h+h));
		diag[i] = 2;
		if(i!=(N-1))
		{
			e[i] = -1;
		}
	}

	gsl_vector_view b1=gsl_vector_view_array (b,N);
	gsl_vector_view diag1 = gsl_vector_view_array (diag,N);
	gsl_vector_view e1 = gsl_vector_view_array (e,N-1) ;
 	gsl_linalg_solve_symm_tridiag(&diag1.vector,&e1.vector,&b1.vector,xt);

}


double poisson(double x)
{
	return((3*x+x*x)*exp(x));
}


void error_plot(const int N)
{
	fprintf(fp,"#x\terror\n");
	init_matrices_LU(N,poisson);
	double err = 0.0,exact = 0.0,x_i=0.0;
	for(int i=0;i<N;i++)
	{
		x_i = i*h+h;
		exact = x_i*(1-x_i)*exp(x_i);
		err = fabs(gsl_vector_get(x,i)-exact)/exact;
		fprintf(fp,"%lf\t%.15lf\n",x_i,err);
	}
	fclose(fp);
}

int main()
{
	clock_t start,stop;
	fp = fopen("N_10.txt","w");
	error_plot(10);

	fp = fopen("N_100.txt","w");
	error_plot(100);

	fp = fopen("N_1000.txt","w");
	error_plot(1000);

	FILE *fp2 = fopen("time_LU.txt","w");
	fprintf(fp2,"#N\ttime\n");
	for(int i=100;i<=1000;i+=100)
	{
		start = clock();
		init_matrices_LU(i,poisson);
		stop=clock();
		fprintf(fp2,"%lf\t%e\n",log(i),log((double)(stop-start)/(CLOCKS_PER_SEC)));
	}
	fclose(fp2);

	fp2 = fopen("time_TD.txt","w");
	fprintf(fp2,"#N\ttime\n");
	int n=1;
	for(int i=7;i<=15;i+=1)
	{
		start = clock();
		init_matrices_TD(pow(2,i),poisson);
		stop=clock();
		fprintf(fp2,"%lf\t%e\n",log(pow(2,i)),log((double)(stop-start)/(CLOCKS_PER_SEC)));
	}
	fclose(fp2);
}
