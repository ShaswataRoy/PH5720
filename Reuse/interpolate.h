/*

CONTENT:

->Interpolate

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/************************************************************************/


double interpolate(double x[],double f[],int n,double x_new)
{
  double result =0.0;
  double lambda =1.0;
  for(int i=0;i<n;i++)
  {
    lambda = 1.0;
    for(int j=0;j<n;j++)
    {
      if(j!=i)
      {
        lambda *= (x_new-x[j])/(x[i]-x[j]);
      }
    }
    result += f[i]*lambda;
  }
  return(result);
}
