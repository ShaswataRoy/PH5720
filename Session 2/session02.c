
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double sec_der(double x,double h)
{
	double res;
	res = (exp(x+h)+exp(x-h)-2*(exp(x)))/(pow(h,2));
	return(res);
}
int main()
{
	FILE *fp;
	fp = fopen("3.dat","w");
	double h;
	double x = 2.0;
	double rel;
	for( h = 1.0; h>= pow(10,-15); h = h/2)
	{
		rel = fabs((sec_der(x,h)-exp(x))/exp(x));
		fprintf(fp, "%e \t %e \t %e \n", h ,sec_der(x,h) ,rel);
	}
	fclose(fp);
	return(0);
}
