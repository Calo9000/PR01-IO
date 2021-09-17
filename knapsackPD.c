#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 10000
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

void dinamicoPrueba(int W, int val[], int wt[], int n)
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
    
    // generar latex
    char archivo[ARRAY_SIZE] = "";
    char inicio[ARRAY_SIZE] = "\\documentclass{article}\n\\usepackage{textcomp}\n\\usepackage{tabularx}\n\\usepackage[table]{xcolor}\n\\begin{document}\n\\begin{center}\n";
    char final[ARRAY_SIZE] = "\\end{center}\n\\end{document}";

    char formula[ARRAY_SIZE] = "\nSe debe maximizar $$Z = ";

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
    strcat(formula, "$$");


    char columnas[ARRAY_SIZE] = "{|";

    for(int i = 0; i<n+1; i++){
        strcat(columnas, "X");
        if (i<n) strcat(columnas, "|");
    }

    strcat(columnas, "|}\n");

    char tablaPD[ARRAY_SIZE] = "\\begin{table}\n\\centering\n\\caption{Programacion Dinamica}\n\\begin{tabularx}{\\textwidth}";

    strcat(tablaPD, columnas);

    char primera_fila[ARRAY_SIZE] = "\\hline";

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

            // PASAR DE SEGUNDOS A MICROSEGUNDOS
            // multiplicar por 1,000,000 (10⁶)

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
    strcat(tablaPD, "\\hline\n\\end{tabularx}\n\\end{table}\n");
                

    // concatenar todo

    /*
    printf("%s\n", tablaPD);
    printf("%s\n", tablaG);
    printf("%s\n", tablaGP);
    */

    
    strcat(archivo, inicio);
    strcat(archivo, formula);
    strcat(archivo, tablaPD);
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
	
    printf("\nValor = %d\n", dinamico(c, valor, peso, n));
    dinamicoPrueba(c, valor, peso, n);
    //int ** tabla = dinamicoPrueba(c, peso, valor, n);
    /*
    for (int i = 0; i<c; i++){
        for(int j=0; j<n; j++){
            printf("\t%d", tabla[i][j]);
        }
    }
    */
    return 0;
}
