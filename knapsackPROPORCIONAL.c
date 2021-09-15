#include <stdio.h>
#include <stdlib.h>

// ALGORITMO GREEDY

int partition(int A[], int B[], int C[], int p, int r) {
    int x = A[p]; // pivot
    int i = p;
    int j = r;
    while (1) {

        while (A[i] > x) {
            i++;
        }

        while (A[j] < x) {
            j--;
        }
        if (i < j) {
            int temp = A[i];
            int temp_peso = B[i];
            int temp_rend = C[i];
            A[i] = A[j];
            B[i] = B[j];
            C[i] = C[j];
            A[j] = temp;
            B[j] = temp_peso;
            C[j] = temp_rend;
        } else {
            return j;
        }
    }
}


void quicksort(int A[], int B[], int C[], int p, int r) {
    if (p < r) {
        int q = partition(A, B, C, p, r);
        quicksort(A, B, C, p, q);
        quicksort(A, B, C, q + 1, r);
    }
}

// Returns the maximum value that can be put in a knapsack of capacity W
int greedy(int C, int valor[], int peso[], int n)
{
    int total = 0;
    int capacidad = C;
    
    int rendimiento[n];

    for(int i; i<n; i++){
        rendimiento[i] = (valor[i]*1000)/peso[i];
        printf("rendimiento %d: %d\n", i, rendimiento[i]);
    }


    quicksort(rendimiento,peso,valor,0,n-1);

    
    printf("\nLista Ordenada \n");
    for (int i=0; i<n; i++) {
        printf("%d",rendimiento[i]);
        if(i<n-1)
            printf(",");
    }
    printf("\n");
    for (int i=0; i<n; i++) {
        printf("%d",valor[i]);
        if(i<n-1)
            printf(",");
    }
    
    
    for (int i = 0; i<n; i++){
        if(peso[i]>=capacidad) continue;
        else{
            total += valor[i];
            capacidad -= peso[i];
        }
    }
    
   return total;
}

int main()
{

	// cantidad de objetos
	int n = rand() % 10;
    printf("Cantidad de objetos: %d\n",n);

	// capacidad del saco
    int  c = rand() % 100;
    printf("Capacidad del saco: %d\n",c);

	int valor[n];
	int peso[n];
	for (int i = 0; i<n; i++){
		// valor de los objetos
		valor[i] = rand() % 10000;
		// peso de los objetos
		peso[i] = rand() % 50;
		printf("Objeto %d-> Valor: %d, Peso: %d\n", i, valor[i], peso[i]);
	}


    printf("\nValor = %d\n", greedy(c, valor, peso, n));
    return 0;
}