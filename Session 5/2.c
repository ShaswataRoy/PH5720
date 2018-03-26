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


double adapt(double eps,double a,double b,int n,double (*func)(double))
{
  double c = (a+b)/2;
  double I=0.0;
  double I1 = Integrate_Trapezoid(a,b,n,func);
  double I0 = Integrate_Trapezoid(a,c,n,func)+Integrate_Trapezoid(c,b,n,func);
  if(fabs(I1-I0)>eps)
  {
    I = adapt(eps/2,a,c,n,func)+adapt(eps/2,c,b,n,func);
  }
  else
  {
    return(I0);
  }
  return(I);
}

double lorentz(double x)
{
  return(1.0/(2.0+x*x));
}

int main()
{
  FILE *fp;
  fp =fopen("output_2.dat","w");
  double err=0.0;
  int n=1;
  double exact = (1.0/sqrt(2))*atan(3/sqrt(2));
  fprintf(fp,"#N\tError Trapezoid\n");
  for(int i=4;i<15;i++)
  {
    n = pow(2,i);
    err= fabs(Integrate_Trapezoid(0,3,n,&lorentz)-exact);
    fprintf(fp,"%.15lf\t%.15lf\n",log(n),log(err));
  }

  fclose(fp);

  fp =fopen("output_tolerance.dat","w");
  fprintf(fp,"#Theoretical\t\tCalculated\tTheoretical>Calculated?\n");
  fprintf(fp,"#Tolerance\t\tTolerance\n");

  double theor_eps=0.0,calc_eps=0.0;
  for(int i=1;i<20;i++)
  {
    theor_eps = pow(3,-i);
    calc_eps= fabs(adapt(theor_eps,0,3,2,&lorentz)-exact)/exact;
    fprintf(fp,"%.13lf\t%.13lf\t%d\n",theor_eps,calc_eps,theor_eps>calc_eps);
  }

}
