#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ARRAY_SIZE_P 10000


void prueba(int W, int val[], int wt[], int n){
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    int i, w;
    int K[n+1][W+1];

    // prueba de programacion dinamica
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
    clock_gettime(CLOCK_REALTIME, &end);
    double tiempo_pd = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;

    // generar latex
    char archivo[ARRAY_SIZE_P] = "";
    char inicio[ARRAY_SIZE_P] = "\\documentclass{article}\n\\usepackage{textcomp}\n\\usepackage{tabularx}\n\\usepackage{fancyhdr}\n\\usepackage{caption}\n\\pagestyle{fancy}\n\\lhead{Modo ejemplo}\n\\rhead{Proyecto 1 IC6400}\n\\usepackage[table]{xcolor}\n\\begin{document}\n\\section*{Resultados del modo de ejemplo}\n\\subsection*{I. Descripción del problema}\nSe tienen 6 objetos con valores y pesos diferentes. Se cuenta con una mochila que solamente es capaz de soportar un peso de 15. Se debe buscar la manera óptima de escoger los objetos que se llevarán en la mochila. Los datos de cada uno de los objetos se muestran en la siguiente tabla:";

    char tablaInicio[ARRAY_SIZE_P] = "\\begin{table}[h]\n\\centering\n\\begin{tabular}{r|rrrrrr}\n& 1 & 2 & 3 & 4 & 5 & 6 \\\\ \\hline\nValor";
    
    for(int i = 0; i<6; i++){
        int valor = val[i];
        char valorstr[4];
        snprintf(valorstr, 4, "%d", valor);
        strcat(tablaInicio, "&");
        strcat(tablaInicio, valorstr);
    }
    strcat(tablaInicio, "\\\\\nPeso");
    for(int i = 0; i<6; i++){
        int peso = wt[i];
        char pesostr[4];
        snprintf(pesostr, 4, "%d", peso);
        strcat(tablaInicio, "&");
        strcat(tablaInicio, pesostr);
    }
    strcat(tablaInicio, "\\\\\n\\end{tabular}\n\\end{table}\n");
    
    char final[ARRAY_SIZE_P] = "\\end{document}";

    
    char formula[ARRAY_SIZE_P] = "\\subsection*{II. Algoritmo de Programación dinámica}\n\nSe debe maximizar $$Z = ";

    for(int i = 0; i<n; i++){
        int valor = val[i];
        char valorstr[4];
        char numerostr[4];
        snprintf(valorstr, 4, "%d", valor);
        strcat(formula, valorstr);
        strcat(formula, "x_");
        snprintf(numerostr, 4, "%d", i+1);
        strcat(formula, numerostr);
        if (i<n-1) strcat(formula, "+");
    }

    strcat(formula, "$$ \nSujeto a $$");

    for(int i = 0; i<n; i++){
        int peso = wt[i];
        char pesostr[4];
        char numerostr[4];
        snprintf(pesostr, 4, "%d", peso);
        strcat(formula, pesostr);
        strcat(formula, "x_");
        snprintf(numerostr, 4, "%d", i+1);
        strcat(formula, numerostr);
        if (i<n-1) strcat(formula, "+");
    }

    strcat(formula, "\\leq ");
    char capacidadstr[4];
    snprintf(capacidadstr, 4, "%d", W);
    strcat(formula, capacidadstr);
    strcat(formula, "$$\nLa siguiente tabla muestra la matriz que se generó al ejecutar el algoritmo de programación dinámica.\n");


    char columnas[ARRAY_SIZE_P] = "{|";

    for(int i = 0; i<n+1; i++){
        strcat(columnas, "X");
        if (i<n) strcat(columnas, "|");
    }

    strcat(columnas, "|}\n");

    char tablaPD[ARRAY_SIZE_P] = "\\begin{table}[h]\n\\centering\n\\caption*{Tabla 2: Matriz resultante del algoritmo de programación dinámica}\n\\begin{tabularx}{\\textwidth}";

    strcat(tablaPD, columnas);

    char primera_fila[ARRAY_SIZE_P] = "\\hline";

    for(int i = 0; i<n; i++){
        int columna = i+1;
        char columnastr[4];
        snprintf(columnastr, 4, "%d", columna);
        strcat(primera_fila, "&");
        strcat(primera_fila, columnastr);
    }
    strcat(primera_fila, " \\\\\n");

    strcat(tablaPD, primera_fila);

    for(int i = 0; i < W; i++){
        int fila = i;
        char filastr[4];
        snprintf(filastr, 4, "%d", fila);
        strcat(tablaPD, "\\hline ");
        strcat(tablaPD, filastr);

        
        for(int j = 0; j < n;j++){
            char buffer[100];


            int x = K[j][i];

            snprintf(buffer, 100, "%d", x);
            strcat(tablaPD,"&");
            
            if(j==0 && x > 0){
                //verde
                strcat(tablaPD,"\\cellcolor{green}");
            } else if (j==0 && x == 0){
                //rojo
                strcat(tablaPD,"\\cellcolor{red}");
            } else if(K[j-1][i] == x){
                //rojo
                strcat(tablaPD,"\\cellcolor{red}");
            } else if(K[j-1][i] != x){
                //verde
                strcat(tablaPD,"\\cellcolor{green}");
            }
            strcat(tablaPD, buffer);

            memset(buffer,0,sizeof(buffer));
            //printf("%s", buffer);
            
        }
        strcat(tablaPD, "\\\\\n");
        

    }
    
    strcat(tablaPD, "\\hline\n\\end{tabularx}\n\\end{table}\n\nResultado obtenido por el algoritmo: ");
    // agregar resultado
    int resultado = K[6][15];
    char resultadostr[32];
    snprintf(resultadostr, 32, "%d", resultado);
    strcat(tablaPD, resultadostr);

    
    // agregar el tiempo de ejecucion
    strcat(tablaPD, "\n\nTiempo de ejecución: ");
    char tiempoPDstr[32];
    snprintf(tiempoPDstr, 32, "%f", tiempo_pd);
    strcat(tablaPD, tiempoPDstr);
    strcat(tablaPD, " segundos.\n");


   // greedy
    clock_gettime(CLOCK_REALTIME, &start);
    int totalG = 0;
    int capacidad = W;
    
    int valorG[n];
    for(int i=0; i<n; i++) valorG[i] = val[i];

    int pesoG[n];
    for(int i=0; i<n; i++) pesoG[i] = wt[i];

    int capacidadG[n];


    quicksort(valorG,pesoG,0,n-1);

    for (int i = 0; i<n; i++){
        if(pesoG[i]>=capacidad){
            capacidadG[i] = capacidad;
            continue;
        }else{
            totalG += valorG[i];
            capacidad -= pesoG[i];
            capacidadG[i] = capacidad;
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double tiempo_g = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;

    char greedy[ARRAY_SIZE_P] = "\\subsection*{III. Algoritmo greedy}\nEn la siguiente tabla se muestran los datos usados por el algoritmo greedy.\n";

    char tablaG[ARRAY_SIZE_P] = "\\begin{table}[h]\n\\centering\n\\begin{tabular}{r|rrrrrr}\n";

    for(int i = 0; i < 3; i++){
        
        for(int j = -1; j < n ;j++){
            if(i==0 && j==-1){
                strcat(tablaG, "Valor");
            } else if(i==1 && j==-1){
                strcat(tablaG, "Peso");
            } else if(i==2 && j==-1){
                strcat(tablaG, "Capacidad Restante");
            } else if(i==0 && j>-1){
                char valorstr[32];
                snprintf(valorstr, 32, "%d", valorG[j]);
                strcat(tablaG, "&");
                strcat(tablaG, valorstr);
            } else if(i==1 && j>-1){
                char pesostr[32];
                snprintf(pesostr, 32, "%d", pesoG[j]);
                strcat(tablaG, "&");
                strcat(tablaG, pesostr);
            } else if(i==2 && j>-1){
                char capacidadstr[32];
                snprintf(capacidadstr, 32, "%d", capacidadG[j]);
                strcat(tablaG, "&");
                strcat(tablaG, capacidadstr);
            }
        }
        strcat(tablaG, "\\\\\n");
        if(i==1) strcat(tablaG, "\\hline ");
    }
    strcat(tablaG, "\\end{tabular}\n\\end{table}\n");
    // agregar resultado
    strcat(tablaG, "\nResultado obtenido por el algoritmo: ");
    char resultadostrG[32];
    snprintf(resultadostrG, 32, "%d", totalG);
    strcat(tablaG, resultadostrG);

    // agregar el tiempo de ejecucion
    strcat(tablaG, "\n\nTiempo de ejecución: ");
    char tiempoGstr[32];
    snprintf(tiempoGstr, 32, "%f", tiempo_g);
    strcat(tablaG, tiempoGstr);
    strcat(tablaG, " segundos.\n");

    strcat(greedy, tablaG);


    // GREEDY PROPORCIONAL
    clock_gettime(CLOCK_REALTIME, &start);

    int totalGP = 0;
    capacidad = W;
    
    int rendimiento[n];
    int capacidadGP[n];

    int valorGP[n];
    for(int i=0; i<n; i++) valorGP[i] = val[i];

    int pesoGP[n];
    for(int i=0; i<n; i++) pesoGP[i] = wt[i];
    
    for(int i=0; i<n; i++){
        float x = ((float)valorGP[i]/(float)pesoGP[i])*1000.0f;
        rendimiento[i] = x;
    }

    quicksortProporcional(rendimiento,pesoGP,valorGP,0,n-1);
    
    for (int i = 0; i<n; i++){
        if(pesoGP[i]>=capacidad) {
            capacidadGP[i] = capacidad;
            continue;
        }else{
            totalGP += valorGP[i];
            capacidad -= pesoGP[i];
            capacidadGP[i] = capacidad;
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    double tiempo_gp = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;

    char proporcional[ARRAY_SIZE_P] = "\\subsection*{IV. Algoritmo greedy proporcional}\nEn la siguiente tabla se muestran los datos usados por el algoritmo greedy proporcional.\n";

    char tablaGP[ARRAY_SIZE_P] = "\\begin{table}[h]\n\\centering\n\\begin{tabular}{r|rrrrrr}\n";

    for(int i = 0; i < 4; i++){        
        for(int j = -1; j < n ;j++){
            if(i==0 && j==-1){
                strcat(tablaGP, "Valor");
            } else if(i==1 && j==-1){
                strcat(tablaGP, "Peso");
            } else if(i==2 && j==-1){
                strcat(tablaGP, "Rendimiento");
            } else if(i==3 && j==-1){
                strcat(tablaGP, "Capacidad Restante");
            } else if(i==0 && j>-1){
                char valorstr[32];
                snprintf(valorstr, 32, "%d", valorGP[j]);
                strcat(tablaGP, "&");
                strcat(tablaGP, valorstr);
            } else if(i==1 && j>-1){
                char pesostr[32];
                snprintf(pesostr, 32, "%d", pesoGP[j]);
                strcat(tablaGP, "&");
                strcat(tablaGP, pesostr);
            } else if(i==2 && j>-1){
                char rendimientostr[32];
                float f = rendimiento[j]/1000.0f;
                snprintf(rendimientostr, 32, "%1.2g", f);
                strcat(tablaGP, "&");
                strcat(tablaGP, rendimientostr);
            } else if(i==3 && j>-1){
                char capacidadstr[32];
                snprintf(capacidadstr, 32, "%d", capacidadGP[j]);
                strcat(tablaGP, "&");
                strcat(tablaGP, capacidadstr);
            }
        }
        strcat(tablaGP, "\\\\\n");
        if(i==2) strcat(tablaGP, "\\hline ");
    }
    strcat(tablaGP, "\\end{tabular}\n\\end{table}\n");
    // agregar resultado
    strcat(tablaGP, "\nResultado obtenido por el algoritmo: ");
    char resultadostrGP[32];
    snprintf(resultadostrGP, 32, "%d", totalGP);
    strcat(tablaGP, resultadostrGP);

    // agregar el tiempo de ejecucion
    strcat(tablaGP, "\n\nTiempo de ejecución: ");
    char tiempoGPstr[32];
    snprintf(tiempoGPstr, 32, "%f", tiempo_gp);
    strcat(tablaGP, tiempoGPstr);
    strcat(tablaGP, " segundos.\n");

    strcat(proporcional, tablaGP);


    // concatenar todo
    strcat(archivo, inicio);
    strcat(archivo, tablaInicio);
    strcat(archivo, formula);
    strcat(archivo, tablaPD);
    strcat(archivo, greedy);
    strcat(archivo, proporcional);
    strcat(archivo, final);
    printf("resultado final:\n\n");

    printf("%s\n", archivo);

    char name[15] = "output_prueba";
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
