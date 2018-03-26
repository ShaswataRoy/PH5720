#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "root.h"


double quad_R(double x)
{
	return(x*x-13);
}

double quad_R_deriv(double x)
{
	return(2*x);
}

int main()
{
	FILE *fp;
	fp = fopen("Problem_1.txt","w");
	fprintf(fp,"#N\tBisection\tNewton_Rhapson\n");
	int N=0;

	for(int i=1;i<10;i++)
	{
		N=2*i;
		fprintf(fp,"%d\t%lf\t%lf\n",N,bisectionN(&quad_R,0,13,N),newton_rhapsonN(&quad_R,&quad_R_deriv,0.1,N));

	}

	fclose(fp);
	return(0);
}
