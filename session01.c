#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long double longfact(int n)
{
  long double res=1;
  for(int i=1;i<=n;i++)
  {
    res*=i;
  }
  return(res);
}

long double calc_expa(double x,int N)
{
  long double result = 0;
  for(int i=0;i<=N;i+=1)
  {
    result=result+powl(-x,i)/longfact(i);
  }
  return(result);
}

double calc_expb(double x,int N)
{
  double result = 1.0;
  double s=1.0;
  for(int i=1;i<=N;i+=1)
  {
    s*=-x/((double)i);
    result=result+s;
  }
  return(result);
}

double calc_expc(double x,int N)
{
  double result = 1.0;
  double s=1.0;
  for(int i=1;i<=N;i+=1)
  {
    s*=x/((double)i);
    result=result+s;
  }
  result=1/result;
  return(result);
}

void main()
{
  FILE *fp;
  fp=fopen("session01a.dat","w");
  long double rel_err=0;
  double x= 0;

  int N;
  printf("Enter x: ");
  scanf("%lf",&x);
  printf("Enter N: ");
  scanf("%d",&N);

  //Part -a

  fprintf(fp,"#N\trel_err\n");
  for(int n=1;n<=N;n+=10)
  {
    rel_err=fabs((calc_expa(x,n)-expl(-x))/expl(-x));
    fprintf(fp,"%d\t%.15Lf\n",n,rel_err);
  }
  fclose(fp);


  //Part -b

  fp=fopen("session01b.dat","w");

  fprintf(fp,"#N\trel_err\n");
  for(int n=1;n<=N;n+=10)
  {
    rel_err=fabs((calc_expb(x,n)-exp(-x))/exp(-x));
    fprintf(fp,"%d\t%.15Lf\n",n,rel_err);
  }
  fclose(fp);

  //Part -c

  fp=fopen("session01c.dat","w");

  fprintf(fp,"#N\trel_err\n");
  for(int n=1;n<=N;n+=10)
  {
    rel_err=fabs((calc_expc(x,n)-exp(-x))/exp(-x));
    fprintf(fp,"%d\t%.15Lf\n",n,rel_err);
  }
  fclose(fp);
}
