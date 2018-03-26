/*

CONTENT:

->bisection
->bisectionN
->newton_rhapson
->newton_rhapsonN
->no_steps_bisection
->no_steps_newton_rhapson

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/************************************************************************/

double bisection(double (*func)(double),double a,double b,double eps)
{
	double c=(a+b)/2;
	if(fabs((*func)(c))<eps)
	{
		return(c);
	}

	if(((*func)(c))*((*func)(a))<0)
	{
		bisection(func,a,c,eps);
	}

	else
	{
		bisection(func,c,b,eps);
	}
}

/************************************************************************/

double bisectionN(double (*func)(double),double a,double b,int N)
{
	N--;
	double c=(a+b)/2;
	if(N==0)
	{
		return(c);
	}

	if(((*func)(c))*((*func)(a))<0)
	{
		bisectionN(func,a,c,N);
	}

	else
	{
		bisectionN(func,c,b,N);
	}
}

/************************************************************************/

int no_steps_bisection(int n,double (*func)(double),double a,double b,double eps)
{
	double c=(a+b)/2;
	if(fabs((*func)(c))<eps)
	{
		return(n+1);
	}

	if(((*func)(c))*((*func)(a))<0)
	{
		no_steps_bisection(n+1,func,a,c,eps);
	}

	else
	{
		no_steps_bisection(n+1,func,c,b,eps);
	}
}

/************************************************************************/

double newton_rhapson(double (*func)(double),double (*deriv)(double),double guess,double eps)
{
	double new_guess=guess-((*func)(guess))/((*deriv)(guess));

	if(fabs((*func)(new_guess))<eps)
	{
		return(new_guess);
	}

	newton_rhapson(func,deriv,new_guess,eps);

}

/************************************************************************/

int no_steps_newton_rhapson(int n,double (*func)(double),double (*deriv)(double),double guess,double eps)
{
	double new_guess=guess-((*func)(guess))/((*deriv)(guess));

	if(fabs((*func)(new_guess))<eps)
	{
		return(n+1);
	}

	no_steps_newton_rhapson(n+1,func,deriv,new_guess,eps);

}

/************************************************************************/

double newton_rhapsonN(double (*func)(double),double (*deriv)(double),double guess,int N)
{
	N--;
	double new_guess=guess-((*func)(guess))/((*deriv)(guess));

	if(N==0)
	{
		return(new_guess);
	}

	newton_rhapsonN(func,deriv,new_guess,N);

}
