#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lista.h"

#define ANSI_COLOR_BLUE    "\x1b[34m"      
#define ANSI_COLOR_ROJO	   "\x1b[1m\x1b[31m"
#define ANSI_COLOR_VERDE    "\x1b[1m\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define CANTIDAD_INICIAL 0
#define POC_INICIAL 0
#define EXITO 0
#define ERROR -1
#define PRIMERA_CANTIDAD 200
#define POSICION 30
#define FUERA_RANGO 100000
#define RANGO_ELIMINACION 50

typedef struct comparacion{
    int elementos[PRIMERA_CANTIDAD];
    int pos;
    bool estado;
}comparacion_t;


void print_test(const char* mensaje, bool ok){
	
    char* color = (ok)?ANSI_COLOR_VERDE:ANSI_COLOR_ROJO; 
    char* estado = (ok)? "OK\n":"ERROR\n";

    printf("  %s*%s => %s%s",color ,mensaje ,estado,ANSI_COLOR_RESET);
}
void print_blue(const char* mensaje){
     printf("%s %s %s.\n",ANSI_COLOR_BLUE,mensaje,ANSI_COLOR_RESET);
}
void completar_elementos(int* elementos,int pos){
    if(pos == PRIMERA_CANTIDAD) return;
    
    elementos[pos] = rand() % 25 + 65;
    completar_elementos(elementos,++pos);    
}
void pruebas_borrar_posicion_inicial_final(lista_t* lista, int* elementos, size_t cant_elementos){
    bool estado = true; 
    lista_borrar_de_posicion(lista, POC_INICIAL);
    print_test("Se borro corectamente de la pocion inicial",elementos[1] == *(int*)lista_elemento_en_posicion(lista, POC_INICIAL));

    size_t poc_final = lista_elementos(lista);    
    lista_borrar_de_posicion(lista, --poc_final);
    print_test("Se borro corectamente de la pocion Final",elementos[--cant_elementos] != *(int*)lista_ultimo(lista));

    poc_final = lista_elementos(lista);
    for (size_t i = 0 ; i < poc_final ; i++) estado = (elementos[i+1] == *(int*)lista_elemento_en_posicion(lista,i));
    print_test("los elementos fueron borrados corectamente",estado);
}
void pruebas_desapilar_ver_tope(lista_t* pila,int* elementos){
    if(lista_vacia(pila)) return;
    
    bool estado = EXITO;   
    
    for(size_t i = 0; i < RANGO_ELIMINACION; i++) estado = lista_desapilar(pila);
    
    print_test("Se desapilo correctamente los elementos", estado == EXITO );

    size_t cant_lista = lista_elementos(pila);
    void* elemento = (cant_lista == CANTIDAD_INICIAL)? NULL:&(elementos[--cant_lista]);
    print_test("El tope de la pila es el correcto", elemento == lista_tope(pila));

    pruebas_desapilar_ver_tope(pila, elementos);
}

void pruebas_desencolar_ver_primero(lista_t* cola,int* elementos ,int* posicion){
    if(lista_vacia(cola)) return;
    
    bool estado = EXITO;   
    
    for(size_t i = 0; i < RANGO_ELIMINACION; i++){ 
        estado = lista_desencolar(cola);
        (*posicion)++;
    }
    print_test("Se desencolo correctamente los elementos", estado == EXITO );
    void* elemento = (lista_vacia(cola))? NULL:&(elementos[*posicion]);
    print_test("El primero de la cola es el correcto",elemento == lista_primero(cola));

    pruebas_desencolar_ver_primero(cola, elementos,posicion);
}
/*Pruebas de las listas*/

void pruebas_listas_null(){
    lista_t* lista = NULL;
    char* ele= "null";
    
    print_test("No se puede borrar en una lista que es igual NULL", lista_insertar(lista, ele) == ERROR);
    print_test("No se puede borrar en una lista que es igual NULL", lista_borrar(lista) == ERROR);
    print_test("No se puede ver el ultimo de una lista es igual NULL",lista_ultimo(lista) == NULL);
    print_test("No se puede borrar en una posicion de la lista que es igual NULL",lista_borrar_de_posicion(lista, POSICION)  == ERROR);
    print_test("No se puede insertar en una posicion de la lista que es igual NULL",lista_insertar_en_posicion(lista, ele,POSICION)  == ERROR);

    lista_destruir(lista);
}
void prueba_lista_vacia(){
    lista_t* lista = lista_crear();

    print_test("lista recien creado esta vacia",lista_vacia(lista));
    print_test("lista cantidad elemonto", lista_elementos(lista) == CANTIDAD_INICIAL);
    
    print_test("No error al intentar borrar en una lista vacia", lista_borrar(lista) == ERROR);

    print_test("el elemento ultimo es NULL", lista_ultimo(lista) == NULL);

    lista_destruir(lista);
}

void pruebas_insertar_borrar(){
    lista_t* lista = lista_crear();
    int elementos[PRIMERA_CANTIDAD];
    completar_elementos(elementos,CANTIDAD_INICIAL);
    bool estado = true;

    for(size_t i = 0; i < PRIMERA_CANTIDAD ; i++) lista_insertar(lista, &(elementos[i]));
    
    print_test("Cantidad Correcta de elementos ",lista_elementos(lista) == PRIMERA_CANTIDAD);

    for (size_t i = 0; i < PRIMERA_CANTIDAD && estado; i++) 
        estado = (elementos[i] == *(char*)lista_elemento_en_posicion(lista ,i));
    print_test("elementos insertado  de forma correcta", estado);   
    
    while (!lista_vacia(lista)) lista_borrar(lista);
    print_test("fue borrado correctamente todos los elementos",lista_vacia(lista)); 

    print_test("La Cantiad de elemento son los correctos", lista_elementos(lista) == CANTIDAD_INICIAL);    

    lista_destruir(lista);
}

void pruebas_insertar_borrar_posicion(){
    lista_t* lista = lista_crear();
    int elementos[PRIMERA_CANTIDAD];
    completar_elementos(elementos, CANTIDAD_INICIAL);
    int estado_insercion = EXITO; 
    bool estado = true;

    for(size_t i = 0; i <PRIMERA_CANTIDAD && estado_insercion == EXITO; i++) 
        estado_insercion = lista_insertar_en_posicion(lista, &(elementos[i]),i);
    
    print_test("Se inserto correcta en las todas la pasicion", estado_insercion == EXITO);

    for (size_t i = 0; i < PRIMERA_CANTIDAD && estado; i++) 
        estado = (elementos[i] == *(char*)lista_elemento_en_posicion(lista ,i));
    print_test("elementos insertado  de forma correcta", estado);   


    for (size_t i = 0;!lista_vacia(lista); i++) lista_borrar_de_posicion(lista, i);

    print_test("Se borraro correctamente los elementos en todas las posicines lista",lista_elementos(lista) == CANTIDAD_INICIAL);
    print_test("La lista esta  vacia ", lista_vacia(lista)); 

    lista_destruir(lista);
}
void pruebas_insertar_borrar_posicion_final_inicio_medio(){        
    lista_t* lista = lista_crear();
    int elementos[PRIMERA_CANTIDAD];
    completar_elementos(elementos, CANTIDAD_INICIAL);
    for(size_t i = 0; i <PRIMERA_CANTIDAD ; i++) lista_insertar(lista, &(elementos[i]));
    
    bool estado = true;
    char* elem_1 = "inicio";
    char* elem_2 = "final";
    char* elem_3 = "medio";
    char* elem_4 = "fuera de rango";
    
    pruebas_borrar_posicion_inicial_final(lista, elementos ,PRIMERA_CANTIDAD);
    
    size_t cantidad_lista = lista_elementos(lista);
    lista_insertar_en_posicion(lista, elem_1, 0); 
    cantidad_lista++;
    size_t posicion_n  =  lista_elementos(lista);
    lista_insertar_en_posicion(lista, elem_2, --posicion_n);
    cantidad_lista++;
    estado = (lista_elemento_en_posicion(lista,0) == elem_1 && lista_elemento_en_posicion(lista,posicion_n) == elem_2);
    print_test("se inserto correctamente en las pocisiones inicio y final",estado);
   
    posicion_n  =  lista_elementos(lista)/2;
    lista_insertar_en_posicion(lista, elem_3,posicion_n);
    cantidad_lista++;
    print_test("Se inserto correctamen en el medio de lista",lista_elemento_en_posicion(lista, posicion_n) == elem_3);

    print_test("cantidad de la lista es correcto", lista_elementos(lista) == cantidad_lista);

    lista_insertar_en_posicion(lista, elem_4, FUERA_RANGO);
    print_test("Eltimo valor de la lista es correcto ", lista_ultimo(lista) == elem_4);
    
    lista_destruir(lista);
}

void pruebas_apilar_desapilar_ver_tope(){
    lista_t* pila = lista_crear();
    int elementos[PRIMERA_CANTIDAD];
    completar_elementos(elementos, CANTIDAD_INICIAL);    
    int estado = EXITO;

    for (size_t i = 0; i < PRIMERA_CANTIDAD; i++) estado = lista_apilar(pila, &(elementos[i]));
    
    print_test("Se apilo correctamente los elementos", estado == EXITO );

    size_t cant_lista = lista_elementos(pila);
    print_test("El tope de la pila es el correcto",elementos[--cant_lista] == *(int*)lista_tope(pila));
    pruebas_desapilar_ver_tope(pila, elementos);
    
    lista_destruir(pila);
}

void pruebas_encolar_desencolar_ver_el_primero(){
    lista_t* cola = lista_crear();
    int elementos[PRIMERA_CANTIDAD];
    completar_elementos(elementos, CANTIDAD_INICIAL);    
    int estado = EXITO;

    for (size_t i = 0; i < PRIMERA_CANTIDAD; i++) estado = lista_apilar(cola, &(elementos[i]));
    
    print_test("Se encolo correctamente los elementos", estado == EXITO );

    print_test("El primero de la cola es el correcto",elementos[POC_INICIAL] == *(int*)lista_primero(cola));

    int posicion = POC_INICIAL;
    pruebas_desencolar_ver_primero(cola, elementos, &posicion);

    lista_destruir(cola);
}
/*
void pruebas_interador_externo(){
    lista_t* lista = NULL;
    lista_iterador_t* iter = lista_iterador_crear(lista);
    print_test("No se puede crear un interador con lista NULL", !(lista_iterador_crear(NULL)));
    print_test("No tiene siguiente el iterador que NULL", !lista_iterador_siguiente(iter));
    print_test("Iterador siguiente devuelve NULL por el iterador es NULL", !lista_iterador_siguiente(iter));

    lista = lista_crear();
    int elementos[PRIMERA_CANTIDAD];
    completar_elementos(elementos,CANTIDAD_INICIAL);
    bool estado = true;
    for (int i = 0; i < PRIMERA_CANTIDAD; i++) lista_insertar(lista,&(elementos[i]));
    
     iter = lista_iterador_crear(lista);
    print_test("iterador tiene siguiente recien creado con elementos en la lista",lista_iterador_tiene_siguiente(iter));
    for (int i = 0;(lista_iterador_tiene_siguiente(iter) && estado);i++)
        estado = (elementos[i] == *(int*)lista_iterador_siguiente(iter));   
    print_test("Se pudo iterar la lista correctamente hasta llegar al final",estado);
    print_test("iterador esta en el final de la lista tiene siguiente",!lista_iterador_siguiente(iter));
    
    lista_iterador_destruir(iter);
    lista_destruir(lista);
}

void comparaciones_de_elementos(void* el1, void* el2){
    comparacion_t* elem = ((comparacion_t*)el2);
    
    if(!(elem->estado)) return;

    elem->estado = (elem->elementos[elem->pos] == *(int*)el1);
    (elem->pos)++;
}

void pruebas_interador_interno(){
    lista_t* lista = lista_crear();
    comparacion_t comparar;
    comparar.pos = 0;
    comparar.estado = true;
    completar_elementos(comparar.elementos, PRIMERA_CANTIDAD);

    lista_con_cada_elemento(lista,comparaciones_de_elementos,&comparar);

    print_test("Todos los elementos son los que tiene que ser con en le iterador interno",comparar.estado);

    lista_destruir(lista);
}*/
int main(){
    print_blue("####  Prueba de lista NULL #####");
    pruebas_listas_null();
    print_blue("####  Prueba de listas vacias #####");
    prueba_lista_vacia();
    print_blue("####  Pruebas de insertar y borrar en la lista #####");
    pruebas_insertar_borrar();
    print_blue("####  Pruebas de insertar y borrar en posiciones en la lista #####");
    pruebas_insertar_borrar_posicion();
    print_blue("####  Pruebas de insertar y borrar en el final, inicio y medio lista #####");
    pruebas_insertar_borrar_posicion_final_inicio_medio();

    print_blue("####  Pruebas de apilar, desapilar y ver tope #####");
    pruebas_apilar_desapilar_ver_tope();
    print_blue("####  Pruebas de encolar, desencolar y ver el primero #####");
    pruebas_encolar_desencolar_ver_el_primero();

/*    print_blue("####  Pruebas de iterador externo #####");
    pruebas_interador_externo();

    print_blue("####  Pruebas de iterador interno #####");
    pruebas_interador_interno();
*/    return 0;
}
