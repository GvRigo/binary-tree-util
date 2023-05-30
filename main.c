/*********************************************************
*  By: GvRigo (Rigoberto Garrido V.)
*
*  Compila:
*      gcc -c arbol.c && gcc -o arbol_bin main.c arbol.o
*
*  Ejecuta:
*      ./arbol_bin <lista-de-numeros>
*********************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "arbol.h"


int main(int argc, char **argv)
{
    Nodo *arbol = NULL;
    int *arreglo_numeros = NULL;

    int tamanio = 0,    opcion = 0;

    procesar_entrada(argc, argv, &arreglo_numeros, &tamanio);
    insertar_arreglo(&arbol, arreglo_numeros, tamanio);

    char cadena[300];
    // Convertir el arreglo de numeros a una cadena de caracteres
    int indice = 0;
    for (int i = 0; i < tamanio; i++) {
        indice += snprintf(cadena + indice, sizeof(cadena) - indice, "%d ", arreglo_numeros[i]);
    }

    limpiar_pantalla();
    do {
        menu(&opcion);
        int valor_nodo = 0;
        switch (opcion) {
            case 1:
                valor_nodo = lee_numero("Introduce el id de nuevo nodo: ");

                limpiar_pantalla();

                insertar(&arbol, valor_nodo);
                printf("Nodo AGREGADO id[%d]\n", valor_nodo);
                break;

            case 2:
                valor_nodo = lee_numero("Introduce id del nodo a eliminar: ");

                limpiar_pantalla();

                int eliminado = eliminar(&arbol, valor_nodo);

                if (eliminado) {
                    printf("\n\t# El nodo [%d] se elimino correctamente del arbol #\n\n", valor_nodo);
                } else {
                    printf("\n\t* El nodo \"%d\" NO se encontro en el arbol *\n\n", valor_nodo);
                }
                break;

            case 3:
                limpiar_pantalla();
                printf("Arreglo de entrada: %s\n\n",cadena);

                printf("Impresion de conjuntos:\n\t");
                imprimir_conjuntos(arbol);

                printf("\n\nARBOL:\n\n");
                mostrar_arbol_rec(arbol, "");
                printf("\n\n");
                break;

            case 4:
                limpiar_pantalla();

                printf("\n\nARBOL:\n\n");
                mostrar_arbol_rec(arbol, "");
                printf("\n\n");

                printf("Preorden:\n\t");
                preorden(arbol);
                printf("\n\n");
                break;

            case 5:
                limpiar_pantalla();

                printf("\n\nARBOL:\n\n");
                mostrar_arbol_rec(arbol, "");
                printf("\n\n");

                printf("Enorden:\n\t");
                inorden(arbol);
                printf("\n\n");
                break;

            case 6:
                limpiar_pantalla();

                printf("\n\nARBOL:\n\n");
                mostrar_arbol_rec(arbol, "");
                printf("\n\n");

                printf("Postorden:\n\t");
                postorden(arbol);
                printf("\n\n");
                break;

            case 7:
                printf("Saliendo...\n");
                break;

            default:
                limpiar_pantalla();
                printf("Opcion Invalida...\n\n");
                break;
        }
        
    } while (opcion != 7);

    
    return 0;
}
