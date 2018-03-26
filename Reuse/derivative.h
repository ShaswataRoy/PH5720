/*

CONTENT:

->deriv:
		*opt 1 = Forward Difference
		*opt 2 = Central Difference
		*opt 3 = Backward Difference
		
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double
deriv(int opt, double x0, double h, double (*func)(double))
{
	double ans;											/*variable that stores the answer*/

	if(opt == 1) /*Forward difference*/
	{
		ans = ((*func)(x0 + h) - (*func)(x0))/h;
	}
	else if(opt == 2) /*Central difference*/
	{
		ans = ((*func)(x0 + h) - (*func)(x0 - h))/(2. * h);
	}
	else if(opt == 3) /*Central difference*/
	{
		ans = ((*func)(x0) - (*func)(x0 - h))/h;
	}
	return(ans);
}
