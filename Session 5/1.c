#include<stdio.h>
#include <math.h>
#include<stdlib.h>

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

double interpolate_new(double x0[],double f0[],int a,int b,double x_new)
{
  double x[b-a+1],f[b-a+1];
  double result =0.0;
  double lambda =1.0;
  int n=b-a+1;
  for(int i=0;i<n;i++)
  {
    x[i]=x0[a+i];
    f[i]=f0[a+i];
  }
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

int main()
{
  FILE *in_ptr;
  in_ptr = fopen("sample_data.dat","r");
  char line[1024];
  fgets(line,sizeof(line),in_ptr);

  int n=0;
  double x_old[9],f_old[9];
  double x_new[201],f_new[201];


  while(fgets(line,sizeof(line),in_ptr)!=NULL)
  {
    sscanf(line,"%lf\t%lf",&x_old[n],&f_old[n]);
    n++;
  }

  int N_old=n;
  fclose(in_ptr);

  //Interpolation using all 9 points

  FILE *out_ptr;
  out_ptr = fopen("output_a.dat","w");
  fprintf(out_ptr,"#E\tCross Section\n");

  for(int i=0;i<=100;i++)
  {
    x_new[i]=2*i;
    f_new[i]=interpolate(x_old,f_old,N_old,x_new[i]);
    fprintf(out_ptr,"%f\t%f\n",x_new[i],f_new[i]);
  }

  fclose(out_ptr);

  //Piecewise interpolation

  out_ptr = fopen("output_b.dat","w");
  fprintf(out_ptr,"#E\tCross Section\n");

  for(int i=0;i<=100;i++)
  {
    x_new[i]=2*i;
    if(i<=25)
    {
      f_new[i]=interpolate_new(x_old,f_old,0,2,x_new[i]);
      fprintf(out_ptr,"%f\t%f\n",x_new[i],f_new[i]);
    }

    else if(i>=25 && i<=50)
    {
      f_new[i]=interpolate_new(x_old,f_old,2,4,x_new[i]);
      fprintf(out_ptr,"%f\t%f\n",x_new[i],f_new[i]);
    }

    else if(i>=50 && i<=75)
    {
      f_new[i]=interpolate_new(x_old,f_old,4,6,x_new[i]);
      fprintf(out_ptr,"%f\t%f\n",x_new[i],f_new[i]);
    }

    else
    {
      f_new[i]=interpolate_new(x_old,f_old,6,8,x_new[i]);
      fprintf(out_ptr,"%f\t%f\n",x_new[i],f_new[i]);
    }
  }

  fclose(out_ptr);


  return(0);
}
