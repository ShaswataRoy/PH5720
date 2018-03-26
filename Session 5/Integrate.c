#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double Integrate_Trapezoid(double a,double b,int n,double (*func)(double))
{
	double h = (b-a)/(double)n,ans=0.0;

	for(int i=0;i<n;i++)
	{
		ans += ((((*func)(a+i*h+h))+((*func)(a+i*h)))/2)*h;
	}

	return(ans);
}
