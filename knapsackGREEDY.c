#include <stdio.h>
#include <stdlib.h>

// ALGORITMO GREEDY

int partition(int A[], int B[], int low, int high) {
    int p = A[high];
    int i = low-1;

    for(int j = low; j <= high - 1; j++){
        if (A[j] > p){
            i++;
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            int Btemp = B[i];
            B[i] = B[j];
            B[j] = Btemp;
        }
    }
    int temp = A[i+1];
    A[i+1] = A[high];
    A[high] = temp;
    return (i+1);
}


void quicksort(int A[], int B[], int low, int high) {
    if(low<high){
        int p = partition(A, B, low, high);
        quicksort(A, B, low, p-1);
        quicksort(A, B, p+1, high);
    }
}



// Returns the maximum value that can be put in a knapsack of capacity W
int greedy(int C, int valor[], int peso[], int n)
{
    int total = 0;
    int capacidad = C;
    
    quicksort(valor,peso,0,n-1);

    /*
    printf("\nLista Ordenada \n");
    for (int i=0; i<n; i++) {
        printf("%d",valor[i]);
        if(i<n-1)
            printf(",");
    }
    printf("\n");
    for (int i=0; i<n; i++) {
        printf("%d",peso[i]);
        if(i<n-1)
            printf(",");
    }
    */
    
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
    int n = rand() % 91 + 10;
    //printf("Cantidad de objetos: %d\n",n);

    // capacidad del saco
    int  c = rand() % 901 + 100;
    //printf("Capacidad del saco: %d\n",c);

    int valor[n];
    int peso[n];
    for (int i = 0; i<n; i++){
        // valor de los objetos
        valor[i] = rand() % 100 + 1;
        // peso de los objetos
        peso[i] = rand() % 4*c/10 + 1;
        //printf("Objeto %d-> Valor: %d, Peso: %d\n", i, valor[i], peso[i]);
    }


    printf("\nValor = %d\n", greedy(c, valor, peso, n));
    return 0;
}