#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define CANT_INICIAL 0
#define ERROR -1
#define EXITO 0
#define INICIO 1
#define ANTE_ULTIMO 2
#define POSICION_INICIAL 0
#define REMOVE 'R'
#define PROC_ELEMENTO 'P'

typedef struct nodo{
    void* dato;
    struct nodo* sig_nodo;
}nodo_t;

struct lista{
    nodo_t* primera_nodo;
    nodo_t* ultimo_nodo;
    size_t cantidad;
};

struct lista_iterador{
    nodo_t* nodo_actual;
};

nodo_t* nodo_crear(void* elemento, nodo_t* sig_nodo){
    
    nodo_t* nodo = malloc(sizeof(nodo_t));

    if(!nodo) return NULL;
    
    nodo->dato = elemento;
    nodo->sig_nodo= sig_nodo;
    
    return nodo;
}

nodo_t** posicionador(nodo_t** nodo, size_t posicion){

    if(posicion == CANT_INICIAL)
        return nodo;      
    
    posicion--;
    
    return posicionador(&((*nodo)->sig_nodo), posicion);
}

int insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion){

    if(!lista) return ERROR;
    
    nodo_t** posicion_a_insertar = posicionador(&(lista->primera_nodo), posicion);   

    nodo_t* nodo_aux = nodo_crear(elemento, *posicion_a_insertar);
    
    if (!nodo_aux) return ERROR;

    *posicion_a_insertar = nodo_aux; 
    lista->cantidad++;    

    return EXITO;
}

int borrar_de_posicion(lista_t* lista, size_t posicion){

    if (!lista) return ERROR;

    nodo_t** nodo_aux = posicionador(&(lista->primera_nodo),posicion);

    nodo_t* nodo_a_eliminar = *nodo_aux;

    *nodo_aux = nodo_a_eliminar->sig_nodo;
    
    free(nodo_a_eliminar);

    lista->cantidad--;
    return  EXITO;
}

void destruir_nodo(void* nodo,void* no_usado){
    no_usado = no_usado;
    free(nodo);
}
 
void recorrer_nodos(nodo_t* nodos, void (*funcion)(void*, void*), void *contexto ,char modo){

    if (!nodos || !funcion) return;
    
    nodo_t* nodo_aux = nodos->sig_nodo;
    void* elemento = (modo == REMOVE)? nodos:nodos->dato; 
    
    funcion(elemento, contexto);
    recorrer_nodos(nodo_aux, funcion, contexto, modo);
}

/// Operaciones De lista. 

lista_t* lista_crear(){

    lista_t* lista = malloc(sizeof(lista_t));
    
    if(!lista) return NULL;
    
    lista->primera_nodo = NULL ;
    lista->ultimo_nodo = NULL;
    lista->cantidad = CANT_INICIAL;
    return lista;
}

int lista_insertar(lista_t *lista, void *elemento){
    
    if(!lista) return ERROR;
    
    nodo_t* nodo = nodo_crear(elemento, NULL); 
    if(!nodo) return ERROR;

    if(!lista->ultimo_nodo)
        lista->primera_nodo = nodo;

    if (lista->ultimo_nodo)
        lista->ultimo_nodo->sig_nodo = nodo;
    
    lista->ultimo_nodo = nodo;
    lista->cantidad++;
            
    return EXITO;
}

int lista_insertar_en_posicion(lista_t *lista, void *elemento, size_t posicion){
    
    int estado = (posicion >= lista_elementos(lista))?
        lista_insertar(lista,elemento):insertar_en_posicion(lista, elemento, posicion);        

    return estado;
}

int lista_borrar(lista_t* lista){
    
    if (!lista || lista_vacia(lista)) return ERROR;

    size_t ante_ultimo = (lista_elementos(lista) == 1)? 0:lista->cantidad - ANTE_ULTIMO; 
    nodo_t** nodo_aux = posicionador(&(lista->primera_nodo), ante_ultimo);
    
    free((*nodo_aux)->sig_nodo);

    lista->ultimo_nodo = *nodo_aux;
    lista->ultimo_nodo->sig_nodo = NULL;
    lista->cantidad--;

    return EXITO;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
    
    int estado = (++posicion >= lista_elementos(lista))? 
        lista_borrar(lista):borrar_de_posicion(lista, --posicion);

    return estado;
}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){ 
    
    bool posicion_valida = (posicion < lista_elementos(lista));
    
    if (!lista || !posicion_valida) return NULL;
    
    nodo_t** nodo_aux = posicionador(&(lista->primera_nodo), posicion);

    return (*nodo_aux)->dato;
}

void* lista_ultimo(lista_t* lista){

    if (lista_vacia(lista)) return NULL;

    return lista->ultimo_nodo->dato;
}

bool lista_vacia(lista_t* lista){

    return (CANT_INICIAL == lista_elementos(lista));
}

size_t lista_elementos(lista_t* lista){

    return (!lista)? CANT_INICIAL:lista->cantidad;    
}

int lista_apilar(lista_t* lista, void* elemento){

    return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista){

    return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){

    return lista_ultimo(lista);

}

int lista_encolar(lista_t* lista ,void* elemento){

    return lista_apilar(lista, elemento);

}

int lista_desencolar(lista_t* lista){

    return lista_borrar_de_posicion(lista, POSICION_INICIAL);

}

void* lista_primero(lista_t* lista){

    return lista_elemento_en_posicion(lista, POSICION_INICIAL);
}

void lista_destruir(lista_t* lista){

    if(!lista) return;

    recorrer_nodos(lista->primera_nodo, destruir_nodo, NULL, REMOVE);

    free(lista);
}

/// Iterador Externo 

lista_iterador_t* lista_iterador_crear(lista_t* lista){
    
    if (!lista) return NULL;
    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    if(!iterador) return NULL;
    
    iterador->nodo_actual = nodo_crear(NULL,lista->primera_nodo);    
    
    if (!(iterador->nodo_actual)){
        free(iterador);
        return NULL;
    }
    
    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){

    return (iterador->nodo_actual->sig_nodo);

}

void* lista_iterador_siguiente(lista_iterador_t* iterador){

    if (!lista_iterador_tiene_siguiente(iterador)) return NULL;

    nodo_t* nodo_aux = iterador->nodo_actual->sig_nodo;

    iterador->nodo_actual = nodo_aux;
    
    return iterador->nodo_actual->dato; 
}

void lista_iterador_destruir(lista_iterador_t* iterador){

    free(iterador);

}

/// iterador Interno de la lista

void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*, void*), void *contexto){
    
    if (!lista ) return;

    recorrer_nodos(lista->primera_nodo, funcion, contexto, PROC_ELEMENTO);   
}