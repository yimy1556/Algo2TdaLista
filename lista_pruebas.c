#include "pruebas.h"
#include "lista.h"

int main(int argc, char const *argv[]){
    
    pruebas_listas_null(NULL);
    
    lista_t* lista = lista_crear();

    prueva_lista_vacia(lista);
    pruevas_insertar(lista);
    pruevas_borrar(lista);
    pruevas_insertar_posicion(lista);
    pruevas_borrar_posicion(lista);
    pruevas_insertar_borrar_posicion_final_inicio_medio(lista);
    lista_destruir(lista);

    lista_t* pila = lista_crear();
    pruebas_apilar_desapilar_ver_tope(pila);
    lista_destruir(pila);
    
    lista_t* cola = lista_crear();
    pruebas_encolar_desencolar_ver_tope(cola);
    lista_destruir(cola);
    return 0;
}
