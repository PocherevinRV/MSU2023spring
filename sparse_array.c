#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double** resizeN(double **a, int max_N, int act_N, int elem_in_row, int size);
double** resizeN(double **a, int max_N, int act_N, int elem_in_row, int size)
{
	double **b,*b1,*b2; int j;  
	b = (double **) malloc (size);	
	b1 = a[0];   
	b[0] = (double *)(b + max_N); 
	for (j = 1; j < act_N; j++)
	{
		b2 = a[j];
		b[j] = b[j-1] + (b2 - b1);                                                                         
		b1 = b2; 	
	}
	if (act_N != 0) 
	{
		b[act_N] = (double *)(b[act_N - 1] + elem_in_row);          	
		for (j = 0; j < (b[act_N] - b[0]); j++) b[0][j] = a[0][j];  
	}
	else
	{	
		for (j = 0; j < elem_in_row; j++) b[0][j] = a[0][j];
	} 
	free(a); return b;
}

int main(void)
{
        int max_N = 1, act_N = 0, max_M = 30, elem_in_row = 0, max_size, act_size = 0, i = 0; double **a; char c; char number[20]; FILE *f;	
	f = fopen("1.txt","r");
	//fscanf(f, "%d", &max_N);
	max_size = max_N*max_M*sizeof(double);
	a = (double **) malloc (max_N*sizeof(double *) + max_size);
	a[0] = (double *)(a + max_N);   	                                             
	while (!feof(f))
	{                                  //  -6
		c = fgetc(f);                                    		
		if (isdigit(c)||c=='-') {number[i] = c; i++;}
		if ((c == ' ' || c == '\t')&&((elem_in_row != 0)||(i!=0))) 
		{
			number[i] = '\0'; i = 0; act_size += sizeof(double);
			//printf("\n!%d/%d, %d/%d!\n",act_size,max_size,act_N,max_N);		
			if (act_size > max_size)
			{       
				
				max_M *= 2;
				max_size =  max_N*max_M*sizeof(double);
				//printf("After:\n!%d/%d, %d/%d!\n",act_size,max_size,act_N,max_N);
				//a = resize(a, max_N, act_N, elem_in_row, max_N*sizeof(double *) + max_size);
				//if (fabs(a[0][0]- 10) > 1e-5) {printf("\n%d %d 1Number: %lf", act_N, max_N, a[0][0]); a[0][0] = 10;}	   	                                             			
			}
			//printf("\nnumber = |%c|\n",number[0]); 
			a[act_N][elem_in_row] = number[0] - '0';
			elem_in_row++;
			//printf("@");
		} 
		if ((c == '\n')&&((elem_in_row != 0)||(i!=0))) 
		{
			if (i != 0) 	
			{
				number[i] = '\0'; i = 0; 
				act_size += sizeof(double);
		 		//printf("\n%d %d Number: %lf", act_N, elem_in_row, a[0][0]);
				if (act_size > max_size)
				{                    
				        max_M *= 2;
					max_size =  max_N*max_M*sizeof(double);
					//a = resize(a, max_N, act_N, elem_in_row, max_N*sizeof(double *) + max_size);
				}
				a[act_N][elem_in_row] = number[0] - '0';			 
				elem_in_row++; 		   
			}
			act_N++; 
			
			if (act_N >= max_N)
			{
				max_N*=2;
				a = resizeN(a, max_N, act_N, elem_in_row, max_N*sizeof(double *) + max_size);
			}
			else
			{
				a[act_N] = a[act_N - 1] + elem_in_row; 
			}
			elem_in_row = 0; 
			//printf("\nRows:%d/%d, Size:%d/%d\n", act_N, max_N, act_size, max_size);
		}
	}
	if (i != 0) 	
	{
		number[i] = '\0'; i = 0; 
		act_size += sizeof(double);
		 //printf("\n%d %d Number: %lf", act_N, elem_in_row, a[0][0]);
		if (act_size > max_size)
		{                    
		        max_M *= 2;
			max_size =  max_N*max_M*sizeof(double);
			//a = resize(a, max_N, act_N, elem_in_row, max_N*sizeof(double *) + max_size);
		}
		a[act_N][elem_in_row] = number[0] - '0';			 
		elem_in_row++; 		   	
	}	
	printf("max_N = %d, act_N = %d\n", max_N, act_N);
                if (act_N + 1 >= max_N)
		{
			max_N+=1; act_N++;
			a = resizeN(a, max_N, act_N, elem_in_row, max_N*sizeof(double *) + max_size);
			act_N--;
		} else {a[act_N+1] = a[act_N] + elem_in_row;}
	//for (i = 0; i < 29; i++) printf("\n|%lf|", a[0][i]);
	//printf("%lf",a[2][1]);
	for (int j=0; j <= act_N; j++)
	{
		for (i = 0; i < a[j+1]-a[j]; i++) printf("%lf ", a[j][i]);
		printf("\n");
	}
	fclose(f);
	free(a);
	return 0;
}