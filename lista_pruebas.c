#include "pruebas.h"
#include "lista.h"

int main(int argc, char const *argv[]){
    
    pruebas_listas_null(NULL);
    
    lista_t* lista = lista_crear();
    prueva_lista_vacia(lista);
    pruevas_insertar(lista);
    pruevas_insertar_posicion(lista);
    pruevas_borrar(lista);
    
    lista_destruir(lista);

    return 0;
}
