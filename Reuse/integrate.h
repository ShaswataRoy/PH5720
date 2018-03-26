/*

CONTENT:

->Trapezoid
->Simpson's Rule 1/3
->Simpson's Rule 3/8

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/************************************************************************/

double
trapezoid(int npts, double a, double b, double (* func) (double))
{														/*counter*/

	double sum;													/*stores the result of integration*/
	double h;														/*value of the function at the end points*/

	/*initialization*/
	sum = 0.;

	h = (b - a)/(double)(npts-1);

	/*evaluating the function between a and b*/
	for(int i = 1; i < npts - 1; i ++)
	{
		sum+= (h/2)*((*func)(a)+(*func)(b));
	}

	return(sum);
}

/**********************************************************************************/


double
simpson_1_3(int npts, double a, double b, double (* func) (double))
{

	double sum;													/*stores the result of integration*/
	double h;						  							/*value of the function at the end points*/

	/*initialization*/
	sum = 0.;

	h = (b - a)/(double)(npts-1);

	/*evaluating the function between a and b*/
	for(int i = 1; i < npts - 1; i ++)
	{
		sum+= (h/6)*(*func)(a)+(*func)(b)+4*(*func)((a+b)/2);
	}

	return(sum);
}

/**********************************************************************************/

double
simpson_3_8(int npts, double a, double b, double (* func) (double))
{

	double sum;													/*stores the result of integration*/
	double h;						  							/*value of the function at the end points*/

	/*initialization*/
	sum = 0.;

	h = (b - a)/(double)(npts-1);

	/*evaluating the function between a and b*/
	for(int i = 1; i < npts - 1; i ++)
	{
		sum+= (h/8)*((*func)(a)+3*(*func)((2*a+b)/3)
														+3*(*func)((a+2*b)/3)+4*(*func)(b));
	}

	return(sum);
}

/**********************************************************************************/
