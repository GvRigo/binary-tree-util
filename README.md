# Binary-tree-util
Un programa interactivo para trabajar con un árbol binario. Inserta, elimina y visualiza nodos, y realiza recorridos preorden, enorden y postorden.

## Requisitos

- Compilador de C compatible, como GCC.
- Bibliotecas estándar de C, incluyendo:
    - `stdio.h`: para entrada/salida estándar.
    - `stdlib.h`: para funciones de gestión de memoria dinámica y utilidades generales.
    - `ctype.h`: para funciones de manipulación de caracteres.
    - `string.h`: para funciones de manipulación de cadenas de caracteres.

Asegúrate de tener un compilador de C instalado en tu sistema y de tener las bibliotecas mencionadas disponibles para poder compilar y ejecutar el programa correctamente.

## Compilación

Para compilar el programa, ejecuta los siguientes comandos:

```bash
gcc -c arbol.c && gcc -o arbol_bin main.c arbol.o
```

## Ejecución

Para ejecutar el programa, utiliza el siguiente comando, (funciona solo con numeros enteros):

```bash
./arbol_bin <lista-de-numeros>
```
### Ejemplo:

```bash
./arbol_bin 5 3 7 0 9 8 1 11 6 2 4
```
