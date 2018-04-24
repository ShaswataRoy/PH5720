#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double euler(int n)
{
	double h = 1.0/n;
	double N[n+1];N[0]=2.;

	for(int i=0;i<n;i++)
	{
		N[i+1] = N[i]-N[i]*h;
	}

	return(N[n]);
}

double rk2(int n)
{
	double h = 1.0/n;
	double N[n+1];N[0]=2.;
	double k=0.,inter=0.;

	for(int i=0;i<n;i++)
	{
		k = h*N[i]/2;
		inter = N[i]-k;
		N[i+1] = N[i]-inter*h;
	}

	return(N[n]);
}

double rk4(int n)
{
	double h = 1.0/n;
	double N[n+1];N[0]=2;
	double k1=0.0,k2=0.0,k3=0.0,k4=0.0;

	for(int i=0;i<n;i++)
	{
		k1 = -h*N[i];
		k2 = -h*(N[i]+k1/2);
		k3 = -h*(N[i]+k2/2);
		k4 = -h*(N[i]+k3);
		N[i+1] = N[i]+(1.0/6)*(k1+2*k2+2*k3+k4);
	}

	return(N[n]);
}

int main()
{
	FILE *fp;
	fp = fopen("Euler.dat","w");
	fprintf(fp,"#N\tRel Error\n");
	double err=0.0;
	for(int i=5;i<15;i++)
	{
		int n = (int)pow(2,i);
		err = fabs(euler(n)-2*exp(-1))/(2*exp(-1));
		fprintf(fp,"%lf\t%lf\n",log(n),log(err));
	}
	fclose(fp);

	fp = fopen("RK2.dat","w");
	fprintf(fp,"#N\tRel Error\n");
	for(int i=5;i<15;i++)
	{
		int n = (int)pow(2,i);
		err = fabs(rk2(n)-2*exp(-1))/(2*exp(-1));
		fprintf(fp,"%lf\t%lf\n",log(n),log(err));
	}
	fclose(fp);

	fp = fopen("RK4.dat","w");
	fprintf(fp,"#N\tRel Error\n");
	for(int i=3;i<10;i++)
	{
		int n = (int)pow(2,i);
		err = fabs(rk4(n)-2*exp(-1))/(2*exp(-1));
		fprintf(fp,"%lf\t%lf\n",log(n),log(err));
	}
	fclose(fp);
	return(0);
}
