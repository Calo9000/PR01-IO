#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE_PD 10000
// PROGRAMACION DINAMICA

int max(int a, int b) { 
	return (a > b)? a : b;
}

int dinamico(int W, int val[], int wt[], int n)
{
   int i, w;
   int K[n+1][W+1];

    // construir la matriz
    for (i = 0; i <= n; i++)
    {
       for (w = 0; w <= W; w++)
       {
           if (i==0 || w==0)
                K[i][w] = 0;
           else if (wt[i-1] <= w)
                K[i][w] = max(val[i-1] + K[i-1][w-wt[i-1]],  K[i-1][w]);
           else
                K[i][w] = K[i-1][w];
            //printf("%d ", K[i][w]);
       }
       //printf("\n");
    }

   return K[n][W];
}

