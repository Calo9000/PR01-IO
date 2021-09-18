#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE_PD 10000
// PROGRAMACION DINAMICA

int max(int a, int b) { 
	return (a > b)? a : b;
}

int dinamico(int c, int valores[], int pesos[], int n)
{
   int i, w;
   int K[n+1][c+1];

    // construir la matriz
    for (i = 0; i <= n; i++)
    {
       for (w = 0; w <= c; w++)
       {
           if (i==0 || w==0)
                K[i][w] = 0;
           else if (pesos[i-1] <= w)
                K[i][w] = max(valores[i-1] + K[i-1][w-pesos[i-1]],  K[i-1][w]);
           else
                K[i][w] = K[i-1][w];
       }
    }

   return K[n][c];
}

