
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

#define ANSI_COLOR_ROJO	   "\x1b[1m\x1b[31m"
#define ANSI_COLOR_VERDE    "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_AZUL  "\x1b[1m\x1b[34m"
#define CANTIDAD_INICIAL 0
#define EXITO 0
#define ERROR -1
#define PRIMERA_CANTIDAD 10
#define POSICION 30
#define FUERA_RANGO 100000


void print_test(const char* mensaje, bool ok){
	
    char* color = (ok)?ANSI_COLOR_VERDE:ANSI_COLOR_ROJO; 
    char* estado = (ok)? "OK\n":"ERROR\n";

    printf("  %s*%s => %s%s",color ,mensaje ,estado,ANSI_COLOR_RESET);
}

void print_blue(char* mensaje){
    
    printf("%s#%s:%s\n",ANSI_COLOR_AZUL, mensaje, ANSI_COLOR_RESET);
}


void completar_elementos(int* elementos,int cantidad){
    if(cantidad < CANTIDAD_INICIAL) return;

    cantidad--;
    elementos[cantidad] = rand() % 25 + 65; 
    completar_elementos(elementos, cantidad);   
}


void prueva_lista_vacia(lista_t* lista){
    print_blue("Verifica los comportamiento de una lista recien creada");
    print_test("lista recien creado esta vacia",lista_vacia(lista));
    print_test("lista cantidad elemonto", lista_elementos(lista) == CANTIDAD_INICIAL);
    
    print_blue("Verifica si devuelve error cuando intenta borrar una lista vacia");   
    print_test("No error al intentar borrar en una lista vacia", lista_borrar(lista) == ERROR);

    print_blue("verifico si el ultimo elemento de una lista vacia es NULL");
    print_test("el elemento ultimo es NULL", lista_ultimo(lista) == NULL);
}

void pruevas_insertar_posicion(lista_t* lista){
    
    bool estado = true;
    char* elem_1 = "inicio";
    char* elem_2 = "final";
    char* elem_3 = "medio";
    char* elem_4 = "fuera de rango";

    print_blue("inserto en el inicio y al final");   
    lista_insertar_en_posicion(lista, elem_1, 0); 
    size_t posicion_n  =  lista_elementos(lista);
    lista_insertar_en_posicion(lista, elem_2, --posicion_n);
    estado = (lista_elemento_en_posicion(lista,0) == elem_1 && lista_elemento_en_posicion(lista,posicion_n) == elem_2);
    print_test("se inserto correctamente en las pocisiones",estado);
   
    print_blue("inserto en medio de la lista");
    posicion_n  =  lista_elementos(lista)/2;
    lista_insertar_en_posicion(lista, elem_3,posicion_n);
    print_test("Se inserto correctamen en el medio de lista",lista_elemento_en_posicion(lista, posicion_n) == elem_3);

    print_blue("Verificar la cantida elementos despues de insertar en diferentes posiciones");
    print_test("cantidad de la lista es correcto", lista_elementos(lista) == 13);
    
    print_blue("Verificar despues de insertar en una posicion que esta fuera de rango");
    lista_insertar_en_posicion(lista, elem_4, FUERA_RANGO);
    print_test("Eltimo valor de la lista es correcto ", lista_ultimo(lista) == elem_4);

}

void pruevas_insertar(lista_t* lista){
    int elementos[PRIMERA_CANTIDAD];
    completar_elementos(elementos, PRIMERA_CANTIDAD);
    bool estado = true;

    for(size_t i = 0; i <PRIMERA_CANTIDAD ; i++) lista_insertar(lista, &(elementos[i]));
    
    print_blue("Verifacia la cantiadad  despues de insertar 10 elementos");
    print_test("Cantidad Correcta de elementos ",lista_elementos(lista) == PRIMERA_CANTIDAD);

    print_blue("Verifico que los elementos estan insertado de forma correcta");
    for (size_t i = 0; i < PRIMERA_CANTIDAD && estado; i++) 
        estado = (elementos[i] == *(char*)lista_elemento_en_posicion(lista ,i));
    print_test("elementos apilados de forma correcta", estado);   
}

void pruevas_borrar(lista_t* lista){
    print_blue("Verificar despues de borrar todos los elementos");
    while (!lista_vacia(lista)) lista_borrar(lista);
    print_test("fue borrado correctamente todos los elementos",lista_vacia(lista)); 

    print_blue("Verifico la cantidad de elementos despues de los anteriores procesos");
    print_test("La Cantiad de elemento son los correctos", lista_elementos(lista) == CANTIDAD_INICIAL);    
}

void pruebas_elementos_posicion(lista_t* lista){
    //print_blue();
    //print_test();
}
void pruevas_borrar_posicion(lista_t* lista);

void pruebas_listas_null(lista_t* lista){
    char* ele= "null";
    print_blue("Verifica si devielve error al usar un lista que es NULL");
    print_test("No se puede borrar en una lista que es igual NULL", lista_insertar(lista, ele) == ERROR);
    print_test("No se puede borrar en una lista que es igual NULL", lista_borrar(lista) == ERROR);
    print_test("El ultimo elemento de una lista que es igual NULL" 
    No se puede ver el ultimo de una lista es igual NULL",lista_ultimo(lista) == NULL);
    print_blue("No se peude ver el ");
    print_test("No se puede borrar en una posicion de la lista que es igual NULL",lista_borrar_de_posicion(lista, POSICION)  == ERROR);
    print_test("No se puede insertar en una posicion de la lista que es igual NULL",lista_insertar_en_posicion(lista, ele,POSICION)  == ERROR);

}