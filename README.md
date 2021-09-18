# PR01-IO
ACERCA DEL PROYECTO:
El proyecto consiste en un programa que presentará 2 opciones de ejecución en las que se resolverá
el famoso problema de la Mochila (Knapsack) utilizando 3 principales algoritmos:

      -Algoritmo de Programación Dinámica
      -Algoritmo Greedy Básico
      -Algoritmo Greedy Proporcional

En el cual se ejecutarán en 2 principales ejecuciones: modo ejemplo y modo experimento.
La elaboración de este proyecto fue realizada en el lenguaje de programación C en un sistema operativo Linux.

INSTRUCCIONES DE UTILIZACIÓN:
1) Para compilar el programa se debe ingresar a la terminal dentro de la carpeta del proyecto. 
   1) a) Antes de compilar/ejecutar el programa es importante instalar pdfLatex para poder visualizar el PDF resultante,
         para esto se debe ingresar el siguiente comando dentro de la terminal que se abrió: sudo apt-get install texlive-latex-base.
2) Dentro de la terminal se debe ingresar el comando "make".
3) Existen varias opciones al momento de iniciar el programa, se puede correr el programa con los siguientes formatos: 

      `./knapsack -X`

   - Donde la primera ejecución corresponde al modo ejemplo del programa en el cuál se resolverá un solo caso aleatorio
   con los 3 algoritmos.

      `./knapsack -E=n`

   - Donde n corresponde al número de casos diferentes -tomando 100n casos- que se resolverán con los 3 algoritmos mencionados.

4) a) Si se ejecuta el primer comando dentro de la terminal, el programa despliegará el siguiente output:
------------
      Ejecutando modo de ejemplo
      Cantidad de objetos: <cantidad de objetos utilizada>
      Capacidad del saco: <capacidad del saco utilizada>
      Objeto 0-> Valor: <valor resultado>, Peso: <peso resultado>
      Objeto 1-> Valor: <valor resultado>, Peso: <peso resultado>
      Objeto 2-> Valor: <valor resultado>, Peso: <peso resultado>
      Objeto 3-> Valor: <valor resultado>, Peso: <peso resultado>
      Objeto 4-> Valor: <valor resultado>, Peso: <peso resultado>
      Objeto 5-> Valor: <valor resultado>, Peso: <peso resultado>
      Algoritmo de programación dinámica:
      Resultado: <Resultado de Programación Dinámica>
      Tiempo de ejecución: <Resultado de su Tiempo de Ejecución>

      Algoritmo greedy:
      Resultado: <Resultado de Algoritmo Greeedy>
      Tiempo de ejecución: <Resultado de su Tiempo de Ejecución>

      Algoritmo greedy proporcional:
      Resultado: <Resultado de Algoritmo Greeedy Proporcional>
      Tiempo de ejecución: <Resultado de su Tiempo de Ejecución>
------------
      *En donde cada valor dentro de <> varía según cada ejecución.*

      Finalmente se despliega una tabla en un PDF con:
      -La descripción del problema junto con la tabla que contiene los respectivos pesos y valores-
      
      -El resultado de la Programación Dinámica en la cual se muestran de color verde los valores que se incluyen dentro de la solución, y en rojo los valores que no se utilizan en la solución. Además aparece la forma matemática del problema inicial. Y finalmente, el resultado obtenido por el algoritmo y el tiempo de ejecución en segundos.
	-El resultado obtenido por medio de cada uno de los algoritmos greedy, acompañado de una tabla que ilustra el proceso por el cual se llegó a esa solución. Finalmente aparece el resultado y el tiempo de ejecución 

	IMPORTANTE: El PDF así como el archivo .tex que se usó para generarlo se guardan en la carpeta del proyecto con el nombre de output.pdf y output.tex respectivamente.

4) b) Si se ejecuta el segundo comando dentro de la terminal, el programa desplegará un documento PDF con 5 tablas en donde:
------------
      -La primera tabla corresponde al tiempo promedio de ejecución con la Programación Dinámica
      -La segunda tabla corresponde al tiempo promedio de ejecución con el Algoritmo Greedy
      -La tercera tabla corresponde al tiempo promedio de ejecución con el Algoritmo Greedy Proporcional
      -La cuarta tabla corresponde el porcentaje de éxitos para el algoritmo Greedy (Es decir que coincide con la solución óptima)
      -La quinta tabla corresponde al porcentaje de éxitos para el algortimo Greedy Proporcional (Es decir que coincide con la solución óptima)

      *En las primeras 3 tablas del documento, los números se presentan en micro segundos.*
      
      IMPORTANTE:  El PDF así como el archivo .tex que se usó para generarlo se guardan en la carpeta del proyecto con el nombre de output_prueba.pdf y output_prueba.tex respectivamente.
