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
    int Btemp = B[i+1];
    B[i+1] = B[high];
    B[high] = Btemp;
    
    return (i+1);
}


void quicksort(int A[], int B[], int low, int high) {
    if(low<high){
        int p = partition(A, B, low, high);
        quicksort(A, B, low, p-1);
        quicksort(A, B, p+1, high);
    }
}



int greedy(int C, int v[], int p[], int n)
{
    int total = 0;
    int capacidad = C;
    
    int valor[n];
    for(int i=0; i<n; i++) valor[i] = v[i];

    int peso[n];
    for(int i=0; i<n; i++) peso[i] = p[i];

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
