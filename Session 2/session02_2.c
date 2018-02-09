#include <stdio.h>
#include <math.h>
#include <string.h>

double second(double x,double h)
{
	double der = (exp(x+h)+exp(x-h)-2*exp(x))/(h*h);
	return(der);
}

void main()
{
	FILE *fp;

	fp=fopen("second_derivative.txt","w");
	int n=1;
	double x=2.0;
	double h,der,rel_err;
	fprintf(fp,"#Precision\tRelative Error\n");
	for(n=1;n<=15;n++)
	{
		h = pow(10,-n);
		der = second(x,h);
		rel_err = (der-exp(x))/exp(x);
		fprintf(fp,"%.15f\t%.15f\n",h,rel_err);
	}
	fclose(fp);
}
