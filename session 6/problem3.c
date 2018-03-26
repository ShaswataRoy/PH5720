#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

//Condition checks whether there exists a root
bool cond = true;
double V0 = 60;

double energy(double E)
{
	double m = 938;
	double hc = 200;
	double a = 1.45;
	double beta = sqrt(m*E)/hc;
	double k = sqrt(m*(V0-E))/hc;

	return(k/tan(k*a)+beta);
}

double energy_deriv(double E)
{
	double m = 938;
	double hc = 200;
	double V0 = 60;
	double a = 1.45;
	double beta = sqrt(m*E)/hc;
	double k = sqrt(m*(V0-E))/hc;
	double dk_dE = -sqrt(m/(V0-E))/(2*hc);
	double dbeta_dE = sqrt(m/E)/(2*hc);

	return(dk_dE*(1/tan(k*a)-(k*a)/(sin(k*a)*sin(k*a)))+dbeta_dE);
}

double newton_rhapson(double (*func)(double),double (*deriv)(double),double guess,double eps,int N)
{
	if(N==0)
	{
		//We have repeated the algorithm N times and yet found no root
		//Hence we assume there is no root and exit the function
		cond=false;
		return(0);
	}

	double new_guess=guess-((*func)(guess))/((*deriv)(guess));

	if(fabs((*func)(new_guess))<eps)
	{
		return(new_guess);
	}

	newton_rhapson(func,deriv,new_guess,eps,N-1);

}

int main()
{
	//eps = required precision for V0
	double eps = 0.0000001;

	while(cond)
	{
		V0=V0-0.000001;
		newton_rhapson(&energy,&energy_deriv,1,eps,50);
	}
	printf("Critical V0: %lf\n",V0);
}
