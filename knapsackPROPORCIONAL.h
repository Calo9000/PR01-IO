#include <stdio.h>
#include <stdlib.h>

// ALGORITMO GREEDY PROPORCIONAL

int partitionProporcional(int A[], int B[], int C[], int low, int high) {
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
            int Ctemp = C[i];
            C[i] = C[j];
            C[j] = Ctemp;
        }
    }
    int temp = A[i+1];
    A[i+1] = A[high];
    A[high] = temp;
    return (i+1);
}


void quicksortProporcional(int A[], int B[], int C[], int low, int high) {
    if(low<high){
        int p = partitionProporcional(A, B, C, low, high);
        quicksortProporcional(A, B, C, low, p-1);
        quicksortProporcional(A, B, C, p+1, high);
    }
}

// Returns the maximum value that can be put in a knapsack of capacity W
int proporcional(int C, int valor[], int peso[], int n)
{

    int total = 0;
    int capacidad = C;
    
    int rendimiento[n];

    for(int i=0; i<n; i++){
        //printf("\nHola \n");
        rendimiento[i] = (valor[i])/peso[i];
        //printf("rendimiento %d: %d\n", i, rendimiento[i]);
    }


    quicksortProporcional(rendimiento,peso,valor,0,n-1);


    /*
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
