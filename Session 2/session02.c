#include <stdio.h>
#include <math.h>
#include <string.h>

double forward(double x,double h)
{
	double der = (exp(x+h)-exp(x))/h;
	return(der);
}

double backward(double x,double h)
{
	double der = (exp(x)-exp(x-h))/h;
	return(der);
}

void main()
{
	FILE *fp;

	fp=fopen("forward_derivative.txt","w");
	int n=1;
	double x=1.0;
	double h,der,rel_err;
	fprintf(fp,"#Precision\tRelative Error\n");
	for(n=1;n<=15;n++)
	{
		h = pow(10,-n);
		der = forward(x,h);
		rel_err = fabs((der-exp(x))/exp(x));
		fprintf(fp,"%.15f\t%.15f\n",log(h),log(rel_err));
	}
	fclose(fp);

	fp=fopen("backward_derivative.txt","w");
	fprintf(fp,"#Precision\tRelative Error\n");
	for(n=1;n<=15;n++)
	{
		h = pow(10,-n);
		der = backward(x,h);
		rel_err = fabs((der-exp(x))/exp(x));
		fprintf(fp,"%.15f\t%.15f\n",log(h),log(rel_err));
	}
	fclose(fp);
}
