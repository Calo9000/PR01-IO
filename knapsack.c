#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "knapsackGREEDY.h"
#include "knapsackPROPORCIONAL.h"
#include "knapsackPD.h"
#include <locale.h>
#include <time.h>

#define ARRAY_SIZE 10000

void generarLatex(double pd[10][10], double g[10][10], double gp[10][10]){

    printf("\n\n");
    // iniciar documento
    char archivo[ARRAY_SIZE] = "";

    char inicio[ARRAY_SIZE] = "\\documentclass{article}\n\\usepackage{textcomp}\n\\usepackage{tabularx}\n\\begin{document}\n\\begin{center}\n";

    // finalizar documento
    char final[ARRAY_SIZE] = "\\end{center}\n\\end{document}";

    // GENERAR LAS 3 TABLAS
    char tablaPD[ARRAY_SIZE] = "\\begin{table}\n\\centering\n\\caption{Programacion Dinamica(\\textmu s)}\n\\begin{tabularx}{0.8\\textwidth}{|X|X|X|X|X|X|X|X|X|X|X|}\n";
    char tablaG[ARRAY_SIZE] = "\\begin{table}\n\\centering\n\\caption{Algoritmo Greedy(\\textmu s)}\n\\begin{tabularx}{0.8\\textwidth}{|X|X|X|X|X|X|X|X|X|X|X|}\n";
    char tablaGP[ARRAY_SIZE] = "\\begin{table}\n\\centering\n\\caption{Algoritmo Greedy Proporcional(\\textmu s)}\n\\begin{tabularx}{0.8\\textwidth}{|X|X|X|X|X|X|X|X|X|X|X|}\n";

    char primera_fila[ARRAY_SIZE] = "\\hline &10&20&30&40&50&60&70&80&90&100\\\\\n";
    strcat(tablaPD, primera_fila);
    strcat(tablaG, primera_fila);
    strcat(tablaGP, primera_fila);

    for(int i = 0; i < 10; i++){
        int fila = (i+1)*100;
        char filastr[4];
        snprintf(filastr, 4, "%d", fila);
        strcat(tablaPD, "\\hline ");
        strcat(tablaPD, filastr);
        strcat(tablaG, "\\hline ");
        strcat(tablaG, filastr);
        strcat(tablaGP, "\\hline ");
        strcat(tablaGP, filastr);
        
        for(int j = 0; j < 10;j++){
            char buffer[9];

            // PASAR DE SEGUNDOS A MICROSEGUNDOS
            // multiplicar por 1,000,000 (10⁶)

            int x = pd[i][j]*1000000;

            snprintf(buffer, 9, "%d", x);
            strcat(tablaPD,"&");
            if(x==0){
                strcat(tablaPD, "$<$1");
            }else{
                strcat(tablaPD, buffer);
            }

            //printf("%s", buffer);

            char buffer1[9];

            //double y = g[i][j];
            int y = g[i][j]*1000000;

            snprintf(buffer1, 9, "%d", y);
            strcat(tablaG,"&");
            if(y==0){
                strcat(tablaG, "$<$1");
            }else{
                strcat(tablaG, buffer1);
            }
            //printf("%s", buffer);

            char buffer2[9];

            //double z = gp[i][j];
            int z = gp[i][j]*1000000;

            snprintf(buffer2, 9, "%d", z);
            strcat(tablaGP,"&");
            if(z==0){
                strcat(tablaGP, "$<$1");
            }else{
                strcat(tablaGP, buffer2);
            }
            //printf("%s", buffer);

        }
        strcat(tablaPD, "\\\\\n");
        strcat(tablaG, "\\\\\n");
        strcat(tablaGP, "\\\\\n");
        

    }
    strcat(tablaPD, "\\hline\n\\end{tabularx}\n\\end{table}\n");
    strcat(tablaG, "\\hline\n\\end{tabularx}\n\\end{table}\n");
    strcat(tablaGP, "\\hline\n\\end{tabularx}\n\\end{table}\n");
                

    // concatenar todo

    /*
    printf("%s\n", tablaPD);
    printf("%s\n", tablaG);
    printf("%s\n", tablaGP);
    */

    
    strcat(archivo, inicio);
    strcat(archivo, tablaPD);
    strcat(archivo, tablaG);
    strcat(archivo, tablaGP);
    strcat(archivo, final);
    printf("resultado final:\n\n");

    printf("%s\n", archivo);
    char name[10] = "output";
    char fileName[70];
	char pdfName[70];

    snprintf(fileName, 90, "./%s.tex", name);
	snprintf(pdfName, 90, "%s.pdf", name);
    FILE *file;

    file = fopen(fileName, "w");
	fprintf(file, "%s\n", archivo);
	fclose(file);

    char pdflatexFile[90];
	char evinceFile[90];

    snprintf(pdflatexFile, 90, "pdflatex %s", fileName);

	snprintf(evinceFile, 90, "evince -s %s", pdfName);
    printf("%s\n", pdflatexFile );
						     
	system(pdflatexFile);
						        
	system(evinceFile);
}

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

    double promedios_pd[10][10], promedios_g[10][10], promedios_gp[10][10];

    int coincidencias_g = 0, coincidencias_gp = 0;
 

    int i, j, k;
    for(i = 0; i<10; i++){
        for(j = 0; j<10; j++){
            //printf("%d, %d\n", i, j);
            double tiempos_pd[n], tiempos_g[n], tiempos_gp[n];
            for(k = 0; k<n; k++){
                //printf("%d\n",i);

                // cantidad de objetos
                int n = (j+1)*10;
                //printf("Cantidad de objetos: %d\n",n);

                // capacidad del saco
                int  c = (i+1)*100;
                //printf("Capacidad del saco: %d\n",c);

                int valor[n];
                int peso[n];
                for (int a = 0; a<n; a++){
                    // valor de los objetos
                    valor[a] = rand() % 100 + 1;
                    // peso de los objetos
                    peso[a] = rand() % 4*c/10 + 1;
                    //printf("Objeto %d-> Valor: %d, Peso: %d\n", i, valor[i], peso[i]);
                }

                struct timespec start, end;

                clock_gettime(CLOCK_REALTIME, &start);
                int pd = dinamico(c, valor, peso, n);
                clock_gettime(CLOCK_REALTIME, &end);
                double d_pd = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
                tiempos_pd[k] = d_pd;
                //printf("Algoritmo de programación dinámica:\nResultado: %d\nTiempo de ejecución: %f\n", pd, d_pd);
                //printf("\n");
                
                clock_gettime(CLOCK_REALTIME, &start);
                //printf("#");
                int gr = greedy(c, valor, peso, n);
                clock_gettime(CLOCK_REALTIME, &end);
                double d_gr = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
                tiempos_g[k] = d_gr;
                //printf("Algoritmo greedy:\nResultado: %d\nTiempo de ejecución: %f\n", gr, d_gr);
                //printf("\n");

                clock_gettime(CLOCK_REALTIME, &start);
                int pr = proporcional(c, valor, peso, n);
                clock_gettime(CLOCK_REALTIME, &end);
                double d_pr = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
                tiempos_gp[k] = d_pr;
                //printf("Algoritmo greedy proporcional:\nResultado: %d\nTiempo de ejecución: %f\n", pr, d_pr);
                //printf("\n");

                
                if(pd==gr){
                    //printf("coincidencia para g\n");
                    coincidencias_g++;
                }
                if(pd==pr){
                    //printf("coincidencia para gp\n");
                    coincidencias_gp++;
                }
                
                //printf("%f %f %f\n", d_pd, d_gr, d_pr);
            }
            //SACAR LOS PROMEDIOS
            double total_pd = 0.0, total_g = 0.0, total_gp = 0.0;
            
            for(int a=0; a<n; a++){
                total_pd += tiempos_pd[a];
                total_g += tiempos_g[a];
                total_gp += tiempos_gp[a];
            }


            double promedio_pd = total_pd/(double)n;
            double promedio_g = total_g/(double)n;
            double promedio_gp = total_gp/(double)n;
            
            //printf("\t%f %f %f\n", promedio_pd, promedio_g, promedio_gp);
            
            promedios_pd[i][j] = promedio_pd;
            promedios_g[i][j] = promedio_g;
            promedios_gp[i][j] = promedio_gp;

            //printf("")

        }
    }

    printf("Tabla PD\n");
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("%f  ",promedios_pd[i][j]);
        }
        printf("\n");
    }
    printf("Tabla Greedy\n");
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("%f  ",promedios_g[i][j]);
        }
        printf("\n");
    }
    printf("Tabla Greedy proporcional\n");
    for(i=0; i<10; i++){
        for(j=0; j<10; j++){
            printf("%f  ",promedios_gp[i][j]);
        }
        printf("\n");
    }

    //printf("Promedio Programación dinámica:\t%f segundos\nPromedio Greedy:\t\t%f segundos\nPromedio greedy proporcional:\t%f segundos\n", promedio_pd, promedio_g, promedio_gp);

    float porcentaje_g  = coincidencias_g/(double)n;
    float porcentaje_gp  = coincidencias_gp/(double)n; 

    //printf("%d %d\n", coincidencias_g, coincidencias_gp);

    printf("\nCoincidencias de algoritmo greedy con el algoritmo PD: \t\t\t%f %%\nCoincidencias del algoritmo greedy proporcional con el algoritmo PD: \t%f %%\n", porcentaje_g,porcentaje_gp);

    generarLatex(promedios_pd, promedios_g, promedios_gp);

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
            if (a>0) experimento(a);
            else printf("Ingrese un número entero mayor que 0");
    }else{
		printf("Argumentos inválidos\n\tIngrese -X si desea ejecutar el modo de ejemplo\n\tIngrese -E=n si desea ejecutar el modo experimento en 100*n casos\n");
    }
	
    return 0;
}