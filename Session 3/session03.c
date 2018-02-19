#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double exp_alpha(double x, void *params)
{
	double alpha = *(double *) params;

	return(exp(alpha * x));
}

double Integrate(int opt,int n,double (*func)(double, void *),void *params_ptr)
{
	double ans=0.0,h;

	if(opt == 1) /*Mid-Point*/
	{
		h = 1/(double)n;
		for(int i=0;i<n;i++)
		{
			ans += ((*func)(i*h+0.5*h, params_ptr))*h;
		}
	}


	else if(opt == 2) /*Trapezoid*/
	{
		h = 1/(double)n;
		for(int i=0;i<n;i++)
		{
			ans += ((((*func)(i*h+h, params_ptr))+((*func)(i*h, params_ptr)))/2)*h;
		}
	}

	return(ans);
}

void main()
{
	FILE *fp;
	fp = fopen("Midpoint.dat","w");
	fprintf(fp,"#Step Size\tRelative Error\n");

	double alpha = 1;
	double rel_err = 0.0,h=0.0;
	int n=0;
	double eval = (exp(alpha)-1)/alpha;
	double calc = 0.0;
	void *param;
	param = &alpha;

	for(int i=0;i<15;i++)
	{
		n = pow(3,i);
		h = 1/(double)n;
		calc = Integrate(1,n,&exp_alpha,param);
		rel_err = fabs((calc-eval)/eval);
		fprintf(fp,"%.15f\t%.15f\n",log(h),log(rel_err));
	}

	fclose(fp);

	fp = fopen("Trapezoid.dat","w");
	fprintf(fp,"#Step Size\tRelative Error\n");

	for(int i=0;i<15;i++)
	{
		n = pow(3,i);
		h = 1/(double)n;
		calc = Integrate(2,n,&exp_alpha,param);
		rel_err = fabs((calc-eval)/eval);
		fprintf(fp,"%.15f\t%.15f\n",log(h),log(rel_err));
	}

	fclose(fp);
}
