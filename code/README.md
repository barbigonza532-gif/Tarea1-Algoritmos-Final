# Documentación

## Entrega

La entrega se realiza vía **aula.usm.cl** en formato `.zip`.

## Multiplicación de matrices

### Programa principal
algoritmos: Fueron obtenidos de la página GeeksforGeeks.
GeeksforGeeks - QuickSort Algorithm
GeeksforGeeks - Merge Sort Algorithm

Descripción: Implementación en C++ de los algoritmos de naive y strassen

Compilador: g++

Resultados: Los resultados de tiempo y memoria de los algoritmos se almacenan en la carpeta matrix_multiplication/data/measurements/.
La primera columna de la izquierda de los archivos representa la dimensión de la matriz, la segunda representa el tiempo y la tercera la memoria ocupada.

### Scripts
plot_generator.py: Script en Python que utiliza pandas y matplotlib.

Lee los archivos naive_results.txt y strassen_results.txt de la carpeta Measurements, promedia las muestras y genera gráficos de Tiempo vs Dimensión y Memoria vs Dimensión en formato PNG.

Comando de ejecución: python scripts/plot_generator.py (se utilizo el entorno Python 3.9.7 (Anaconda), para que leyera las librerías).
los scripts deben ejecutarse desde la carpeta (matrix_multiplication/) para que las rutas relativas de los datos funcionen.

Resutados: \code\matrix_multiplication\data\plots

## Ordenamiento de arreglo unidimensional
Algoritmos: MergeSort, QuickSort, std::sort.

### Programa principal
Algoritmos: Fueron obtenidos de la página GeeksforGeeks.
Program to multiply two matrices - GeeksforGeeks (naive)
Strassen's Matrix Multiplication Algorithm | Implementation - geeksforgeeks (strassen)

Descripción: Implementación en C++ de tres algoritmos de ordenamiento eficientes

Compilador: g++

Pruebas: Se realizaron mediciones con arreglos de tamaño N desde 10^1 hasta 10^7

Resultados: Los resultados de tiempo y memoria de los algoritmos se almacenan en la carpeta sorting/data/measurements/.
La primera columna de la izquierda de los archivos representa el tamaño del arreglo, la segunda representa el tiempo y la tercera la memoria ocupada.

### Scripts
plot_generator.py: Script en Python que utiliza pandas y matplotlib.

Lee los archivos sort_results.txt, mergesort_results.txt y quicksort_results.txt de la carpeta Measurements, promedia las muestras y genera gráficos de Tiempo vs Dimensión y Memoria vs Dimensión en formato PNG.

Comando de ejecución: python scripts/plot_generator.py (se utilizo el entorno Python 3.9.7 (Anaconda), para que leyera las librerías).
los scripts deben ejecutarse desde las carpetas (sorting/) para que las rutas relativas de los datos funcionen.

Resultados: \code\sorting\data\plots


