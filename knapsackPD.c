#include <stdio.h>
#include <stdlib.h>

// PROGRAMACION DINAMICA

int max(int a, int b) { 
	return (a > b)? a : b;
}

int dinamico(int W, int wt[], int val[], int n)
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


int main()
{

	// cantidad de objetos
	int n = 6;
    printf("Cantidad de objetos: %d\n",n);

	// capacidad del saco
    int  c = 15;
    printf("Capacidad del saco: %d\n",c);

	int valor[n];
	int peso[n];
	for (int i = 0; i<n; i++){
		// valor de los objetos
		valor[i] = rand() % 20 + 1;
		// peso de los objetos
		peso[i] = rand() % 7 + 1;
		printf("Objeto %d-> Valor: %d, Peso: %d\n", i, valor[i], peso[i]);
	}
	

    printf("\nValor = %d\n", dinamico(c, peso, valor, n));
    return 0;
}
