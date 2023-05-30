#ifndef ARBOL_H
#define ARBOL_H


typedef struct nodo
{
    int valor;
    struct nodo *padre, 
                *izqdo,  // menor
                *dercho; // mayor
} Nodo;


Nodo* crear_nodo(int, Nodo *);
void destruir_nodo(Nodo* nodo);

void procesar_entrada(int argc, char **, int **, int *);
void insertar_arreglo(Nodo **, int [], int);
void imprimir_conjuntos(Nodo *);
void mostrar_arbol_rec(Nodo *, char *);

void insertar_con_padre(Nodo **, Nodo *, int);
void insertar(Nodo **, int);

Nodo* encontrar_minimo(Nodo *);
int eliminar(Nodo **, int);

void preorden(Nodo *);
void inorden(Nodo *);
void postorden(Nodo *);

//funciones auxiliares input-output
void menu (int *);
int es_entero(const char *);
int lee_numero(char *);
void limpiar_pantalla();

#endif

