/*
Shaswata Roy 	20/03/18
PURPOSE: Finding the lowest eigenvalue of a hamiltonian
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
#include <gsl/gsl_matrix.h>

int main()
{
	//Get Input

	FILE *mesh_ptr,*pot_ptr;
	mesh_ptr = fopen("kmesh_wts.dat","r");
	pot_ptr = fopen("matrix_elements.dat","r");

	double k[54],w_k[54];
	double kdum,kpdum;
	double H[54][54];
	double H_arr[54*54];
	double h_m = 197.32705;

	int n =0,m=0;
	char line[1024];

	while(fgets(line,sizeof(line),mesh_ptr)!= NULL)
	{
		sscanf(line,"%lf %lf", &k[n], &w_k[n]);
		n++;
	}

	int Nkmax = n;

	fgets(line,sizeof(line),pot_ptr);
	fgets(line,sizeof(line),pot_ptr);
	fgets(line,sizeof(line),pot_ptr);

	n=0;

	double v[54][54];



	while(fgets(line,sizeof(line),pot_ptr)!=NULL)
	{
		sscanf(line,"%lf %lf %lf",&kdum,&kpdum,&v[n][m]);
		n++;

		if(n==Nkmax)
		{
			m++;
			n=0;
		}
	}

	fclose(mesh_ptr);
	fclose(pot_ptr);

	//Hamiltonian

	for(int i=0;i<54;i++)
	{
		for(int j=0;j<54;j++)
		{
			if(i==j)
			{
				H[i][j] = h_m*(k[i]*k[i]/2+(2/M_PI)*k[i]*sqrt(w_k[i])*v[i][j]*k[j]*sqrt(w_k[j]));
			}

			else
			{
				H[i][j] = h_m*((2/M_PI)*k[i]*sqrt(w_k[i])*v[i][j]*k[j]*sqrt(w_k[j]));
			}
		}
	}

	for (int i=0; i<54; i++)
	{
		for (int j=0; j<54; j++)
		{
			H_arr[i*54+j]=H[i][j];
		}
	}


	//Finding the eigenvalues of the matrix H

	gsl_matrix_view H_mat = gsl_matrix_view_array (H_arr, 54, 54);


  	gsl_vector *eval = gsl_vector_alloc (54);
  	gsl_matrix *evec = gsl_matrix_alloc (54, 54);

  	gsl_eigen_symmv_workspace * w = gsl_eigen_symmv_alloc (54);

  	gsl_eigen_symmv (&H_mat.matrix, eval, evec, w);

  	gsl_eigen_symmv_free (w);

  	gsl_eigen_symmv_sort (eval, evec,GSL_EIGEN_SORT_VAL_ASC);

  	printf("Lowest Eigenvalue of the Hamiltonian : %lf\n" ,gsl_vector_get(eval,0));

  	gsl_vector_free (eval);
  	gsl_matrix_free (evec);

}
