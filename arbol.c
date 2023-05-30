#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arbol.h"

#define MAX_TAM_CADENA 1000


Nodo* crear_nodo(int valor, Nodo *padre)
{
    Nodo* nuevo_nodo = (Nodo*) malloc(sizeof(Nodo));
    nuevo_nodo->valor = valor;
    nuevo_nodo->padre = padre;  // asignamos padre
    nuevo_nodo->izqdo = nuevo_nodo->dercho = NULL;
    return nuevo_nodo;
}


void destruir_nodo(Nodo* nodo)
{
    nodo->izqdo = nodo->dercho = NULL;
    free(nodo);
}


void procesar_entrada(int argc, char **argv, int **arreglo_entrada, int *tamano)
{
    if (argc < 2) {
        printf("Error: no se ingresaron valores\n");
        exit(1);
    }

    *arreglo_entrada = (int *)malloc((argc - 1) * sizeof(int));
    for (int i = 1; i < argc; i++) {
        (*arreglo_entrada)[i - 1] = atoi(argv[i]);
    }

    *tamano = argc - 1;
}


void insertar_arreglo(Nodo **arbol, int arreglo[], int tamano)
{
    for (int i = 0; i < tamano; i++) {
        insertar(arbol, arreglo[i]);
    }
}


void imprimir_conjuntos(Nodo *arbol)
{
    if (arbol == NULL) {
        /*printf("[]");  // Imprimir conjunto vacío*/
        return;
    }

    printf("%d", arbol->valor);  // Imprimir valor del nodo

    if (arbol->izqdo != NULL || arbol->dercho != NULL) {
        printf("(");  // Abrir parentesis para el conjunto
        imprimir_conjuntos(arbol->izqdo);  // Imprimir subarbol izquierdo

        if (arbol->izqdo && arbol->dercho) {
            printf(",");  // Imprimir coma para separar los conjuntos
        }

        imprimir_conjuntos(arbol->dercho);  // Imprimir subarbol derecho
        printf(")");  // Cerrar parentesis para el conjunto
    }
}


/*
 *  \u2500 para el carácter ─ (línea horizontal)
 *  \u2514 para el carácter └ (esquina inferior izquierda)
 *  \u251C para el carácter ├ (rama intermedia)
 *  \u2524 para el carácter ┤ (rama final)
 *  \u2502 para el carácter │ (línea vertical)
*/
void mostrar_arbol_rec(Nodo *nodo, char *cadena)
{
    printf("%d\n", nodo->valor);

    // para hijo izqdo
    if (nodo->izqdo) {
        char cadena2[MAX_TAM_CADENA];       strcpy(cadena2, cadena);
        if (nodo->dercho) {
            printf("%s\u251C\u2500\u2500 ", cadena);    //├──  son 4 caracteres con espacio
            char *linea = "\u2502";         strcat(cadena2, linea);  // │

            strcat(cadena2, "   ");        // son 3 caracteres
            mostrar_arbol_rec(nodo->izqdo, cadena2);

        } else {
            printf("%s\u2514\u2500\u2500 ", cadena);    // └── 
            strcat(cadena2, "    ");        // son 4 caracteres
            mostrar_arbol_rec(nodo->izqdo, cadena2);
        }
    }
    // para el hijo dercho
    if (nodo->dercho) {
        char cadena3[MAX_TAM_CADENA];       strcpy(cadena3, cadena);
        printf("%s\u2514\u2500\u2500 ", cadena);        // └── 
        strcat(cadena3, "    ");        // son 4 caracteres
        mostrar_arbol_rec(nodo->dercho, cadena3);
    }
}


void insertar_con_padre(Nodo **arbol, Nodo *padre, int valor)
{
     if (*arbol == NULL) {
         *arbol = crear_nodo(valor, padre);
    } else {
         int valor_raiz = (*arbol)->valor;
         if (valor < valor_raiz) {
                                    //arbol     //padre  //valor
            insertar_con_padre(&(*arbol)->izqdo, *arbol, valor);  // vamos por el izqdo
        } else
            insertar_con_padre(&(*arbol)->dercho, *arbol, valor); // vamos por mayor
    }
}


void insertar(Nodo **arbol, int valor)
{
    insertar_con_padre(arbol, NULL, valor);  // el padre raiz no tiene padre
}


Nodo* encontrar_minimo(Nodo *nodo)
{
    Nodo* actual = nodo;
    while (actual->izqdo != NULL) {
        actual = actual->izqdo;
    }
    return actual;
}


int eliminar(Nodo** raiz, int valor)
{
    if (*raiz == NULL) {
        return 0;  // Si el árbol está vacío, no se hace nada
    }
    if (valor < (*raiz)->valor) {
        eliminar(&(*raiz)->izqdo, valor);  // El valor a eliminar es menor, buscar en el subárbol izquierdo
    } else if (valor > (*raiz)->valor) {
        eliminar(&((*raiz)->dercho), valor);  // El valor a eliminar es mayor, buscar en el subárbol derecho
    } else {
        // Se encontró el valor a eliminar
        if ((*raiz)->izqdo == NULL) {
            // El nodo a eliminar no tiene hijo izquierdo
            Nodo* temp = (*raiz)->dercho;
            free(*raiz);
            *raiz = temp;
        } else if ((*raiz)->dercho == NULL) {
            // El nodo a eliminar no tiene hijo derecho
            Nodo* temp = (*raiz)->izqdo;
            free(*raiz);
            *raiz = temp;
        } else {
            // El nodo a eliminar tiene ambos hijos
            Nodo* temp = encontrar_minimo((*raiz)->dercho);
            (*raiz)->valor = temp->valor;
            eliminar(&((*raiz)->dercho), temp->valor);
        }
        return 1;
    }
    return 0;
}


void preorden(Nodo* raiz)
{
    if (raiz == NULL) {
        /*printf("~");*/
    }
    if (raiz != NULL) {
        /*printf("(");*/
        printf("%d ", raiz->valor);
        preorden(raiz->izqdo);
        preorden(raiz->dercho);
        /*printf(")");*/
    }
}


void postorden(Nodo* raiz)
{
    if (raiz == NULL) {
        /*printf("~");*/
    }
    if (raiz != NULL) {
        /*printf("(");*/
        postorden(raiz->izqdo);
        postorden(raiz->dercho);
        printf("%d ", raiz->valor);
        /*printf(")");*/
    }
}

void inorden(Nodo *arbol)
{
    if (arbol == NULL) {
        /*printf("~");*/
    }
    if (arbol != NULL){
        /*printf("(");*/
        inorden(arbol->izqdo);
        printf("%d ", arbol->valor);
        inorden(arbol->dercho);
        /*printf(")");*/
    }
}


// Funciones auxiliares input-output  *
void menu (int *opcion)
{
    printf("╔══════════════════════╗\n");
    printf("║       M E N Ú        ║\n");
    printf("╠══════════════════════╣\n");
    printf("║ 1. Insertar          ║\n");
    printf("║ 2. Eliminar          ║\n");
    printf("║ 3. Imprimir          ║\n");
    printf("║ 4. Preorden          ║\n");
    printf("║ 5. Enorden           ║\n");
    printf("║ 6. Postorden         ║\n");
    printf("║ 7. Salir             ║\n");
    printf("╚══════════════════════╝\n");

    *opcion = lee_numero("Seleccione una opcion: ");
}


int lee_numero(char *cadena)
{
    char aux[10];
    int id;
    do {
        printf("%s", cadena);
        scanf("%s", aux);

        if (!es_entero(aux)) {
        printf("\t  Ingrese un numero valido!!\n");
        }
    } while (!es_entero(aux));

    id = atoi(aux);  // convertimos de cadena a entero
    return id;
}


int es_entero(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {  // Recorremos la cadena
        if (!isdigit(str[i])) {  // Verifica si elemento_del_indice es digito
            return 0;
        }
    }
    return 1;
}


void limpiar_pantalla(void)
{
    #ifdef _WIN32
        system("cls"); // ejecutando en Windows
    #else
        system("clear"); // ejecutando en Unix/Linux/Mac
    #endif
}
