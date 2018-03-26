#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "root.h"

double energy(double E)
{
	double m = 938;
	double hc = 200;
	double V0 = 60;
	double a = 1.45;
	double beta = sqrt(m*E)/hc;
	double k = sqrt(m*(V0-E))/hc;

	return(k/tan(k*a)+beta);
}

double energy_deriv(double E)
{
	double m = 938;
	double hc = 200;
	double V0 = 60;
	double a = 1.45;
	double beta = sqrt(m*E)/hc;
	double k = sqrt(m*(V0-E))/hc;
	double dk_dE = -sqrt(m/(V0-E))/(2*hc);
	double dbeta_dE = sqrt(m/E)/(2*hc);

	return(dk_dE*(1/tan(k*a)-(k*a)/(sin(k*a)*sin(k*a)))+dbeta_dE);
}

int main()
{
	FILE *fp;
	//Generating data points to plot the function
	fp = fopen("function.txt","w");
	fprintf(fp,"#x\tf(x)\n");

	for(double x=0.0;x<5;x=x+0.1)
	{
		fprintf(fp,"%lf\t%lf\n",x,energy(x));

	}

	fclose(fp);

	fp = fopen("Problem_2.txt","w");
	fprintf(fp,"#N\tBisection\tNewton_Rhapson\n");
	fprintf(fp,"%d\t%lf\t%lf\n",0,1.0,0.1);
	int N=0;

	for(int i=1;i<10;i++)
	{
		N=2*i;
		fprintf(fp,"%d\t%lf\t%lf\n",N,bisectionN(&energy,0.5,1.5,N),newton_rhapsonN(&energy,&energy_deriv,0.1,N));

	}

	fclose(fp);

	//Predefined accuracy= 0.000001
	double prec = 0.000001;
	printf("Number of Steps :\n");
	printf("(a) Bisection:%d \n",no_steps_bisection(0,&energy,0.5,1.5,prec));
	printf("(b) Newton Raphson:%d \n",no_steps_newton_rhapson(0,&energy,&energy_deriv,0.1,prec));
	return(0);
}
