#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "knapsackGREEDY.h"
#include "knapsackPROPORCIONAL.h"
#include "knapsackPD.h"

int ejemplo(){

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

    clock_t begin = clock();
    int pd = dinamico(c, valor, peso, n);
    clock_t end = clock();
    double d_pd = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Algoritmo de programación dinámica:\nResultado: %d\nTiempo de ejecución: %f\n", pd, d_pd);
    printf("\n");
    begin = clock();
    int gr = greedy(c, valor, peso, n);
    end = clock();
    double d_gr = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Algoritmo greedy:\nResultado: %d\nTiempo de ejecución: %f\n", gr, d_gr);
    printf("\n");
    begin = clock();
    int pr = proporcional(c, valor, peso, n);
    end = clock();
    double d_pr = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Algoritmo greedy proporcional:\nResultado: %d\nTiempo de ejecución: %f\n", pr, d_pr);
    printf("\n");

    return 0;

}

int experimento(int n){

    for(int i = 0; i<10*n; i++){
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

        struct timespec start, end;

        clock_gettime(CLOCK_REALTIME, &start);
        int pd = dinamico(c, valor, peso, n);
        clock_gettime(CLOCK_REALTIME, &end);
        double d_pd = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
        printf("Algoritmo de programación dinámica:\nResultado: %d\nTiempo de ejecución: %f\n", pd, d_pd);
        printf("\n");
        clock_gettime(CLOCK_REALTIME, &start);
        printf("#");
        int gr = greedy(c, valor, peso, n);
        clock_gettime(CLOCK_REALTIME, &end);
        double d_gr = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
        printf("Algoritmo greedy:\nResultado: %d\nTiempo de ejecución: %f\n", gr, d_gr);
        printf("\n");
        clock_gettime(CLOCK_REALTIME, &start);
        int pr = proporcional(c, valor, peso, n);
        clock_gettime(CLOCK_REALTIME, &end);
        double d_pr = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
        printf("Algoritmo greedy proporcional:\nResultado: %d\nTiempo de ejecución: %f\n", pr, d_pr);
        printf("\n");
    }

    return 0;

}

int main(int argc, char* argv[]){

    //printf("%s\n",argv[1]);

    if(argc != 2){
		printf("Argumentos inválidos\n\tIngrese -X si desea ejecutar el modo de ejemplo\n\tIngrese -E=n si desea ejecutar el modo experimento en 100*n casos\n");
		exit(0);
	}else if(strcmp(argv[1], "-X")==0){
            printf("Ejecutando modo de ejemplo\n");
            ejemplo();
    }else if(argv[1][0]=='-' && argv[1][1]=='E' && argv[1][2]=='='){
            printf("Ejecutando modo de experimento\n");
            char* c = argv[1]+3;
		    int a = atoi(c);
            //printf("%d\n", a);
            experimento(a);
    }else{
		printf("Argumentos inválidos\n\tIngrese -X si desea ejecutar el modo de ejemplo\n\tIngrese -E=n si desea ejecutar el modo experimento en 100*n casos\n");
    }
	
    return 0;
}