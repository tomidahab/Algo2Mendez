#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>

lista_t* lista_crear(){
    
    lista_t* lista = malloc(sizeof(lista_t));

    lista->cantidad = 0;
    lista->nodo_inicio = NULL;
    lista->nodo_fin = NULL;

    if (!lista)
        return NULL;

    return lista;
}

int lista_insertar(lista_t* lista, void* elemento){

    if (!lista)
        return -1;

    nodo_t* nodo_a_agregar = malloc(sizeof(nodo_t));


    if (!nodo_a_agregar)
        return -1;

    lista->cantidad++;

    nodo_a_agregar->elemento = elemento;
    nodo_a_agregar->siguiente = NULL;

    if (lista->nodo_inicio == NULL){

        lista->nodo_inicio = nodo_a_agregar;
        lista->nodo_fin = nodo_a_agregar;
        return 0;
    }

    lista->nodo_fin->siguiente = nodo_a_agregar;
    lista->nodo_fin = nodo_a_agregar;

    return 0;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
    
    if (!lista)
        return -1;
    
    if (posicion >= lista->cantidad)
        return lista_insertar(lista, elemento);

    nodo_t* nodo_a_agregar = malloc(sizeof(nodo_t));


    if (!nodo_a_agregar)
        return -1;

    lista->cantidad++;

    nodo_a_agregar->elemento = elemento;
    nodo_a_agregar->siguiente = NULL;

    if (lista->nodo_inicio == NULL && posicion == 0){

        lista->nodo_inicio = nodo_a_agregar;
        lista->nodo_fin = nodo_a_agregar;
        return 0;
    }


    if (posicion == 0){

        nodo_a_agregar->siguiente = lista->nodo_inicio;
        lista->nodo_inicio = nodo_a_agregar;
        return 0;

    }

    nodo_t* nodo_antes_a_insertar = lista->nodo_inicio;

    while(posicion != 0){

        if (posicion == 1){

            nodo_t* auxiliar = nodo_antes_a_insertar->siguiente;
            nodo_antes_a_insertar->siguiente = nodo_a_agregar;
            nodo_a_agregar->siguiente = auxiliar;

        }
        nodo_antes_a_insertar = nodo_antes_a_insertar->siguiente;
        posicion--;
    }

    return 0;
}

void nodo_eliminar_ultimo(nodo_t* nodo){

    if (nodo->siguiente)
        nodo_eliminar_ultimo(nodo->siguiente);
    else{
        //free(nodo->elemento);
        free(nodo);
    }
}

int lista_borrar(lista_t* lista){

    if(!lista || lista->cantidad == 0)
        return -1;

    if (lista->cantidad == 1){

        nodo_eliminar_ultimo(lista->nodo_inicio);
        lista->cantidad = 0;
        lista->nodo_inicio = NULL;
        lista->nodo_fin = NULL;
        return 0;
    }

    size_t posicion = lista->cantidad;

    nodo_eliminar_ultimo(lista->nodo_inicio);

    nodo_t* nodo_actual = lista->nodo_inicio;

    while (posicion != 1){

        posicion--;

        if (posicion == 1){

            lista->nodo_fin = nodo_actual;
            nodo_actual->siguiente = NULL;

        }
        else
            nodo_actual = nodo_actual->siguiente;
    }

    lista->cantidad--;

    return 0;
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){

    if(!lista || lista->cantidad == 0)
        return -1;

    if (lista->cantidad == 1 || posicion + 1 >= lista->cantidad)
        return lista_borrar(lista);

    size_t posicion_actual = 0;

    nodo_t* nodo_actual = lista->nodo_inicio;

    if (posicion_actual == posicion){

        nodo_t* auxiliar = nodo_actual->siguiente;

        //free(nodo_actual->elemento);
        free(nodo_actual);

        lista->nodo_inicio = auxiliar;

    }

    while (posicion_actual != posicion){

        posicion_actual++;

        if (posicion_actual == posicion){

            nodo_t* auxiliar = nodo_actual->siguiente->siguiente;
            //free(nodo_actual->siguiente->elemento);
            free(nodo_actual->siguiente);
            nodo_actual->siguiente = auxiliar;

        }

    }

    lista->cantidad--;

    return 0;
}

void* elemento_en_posicion(nodo_t* nodo_actual, size_t posicion_actual){

    if (posicion_actual == 0)
        return nodo_actual->elemento;
    else
        return elemento_en_posicion(nodo_actual->siguiente,posicion_actual-1);

}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
    
    if(!lista || posicion + 1 > lista->cantidad)
        return NULL;

    return elemento_en_posicion(lista->nodo_inicio,posicion);
}

void* lista_ultimo(lista_t* lista){

    if (!lista || lista->cantidad == 0)
        return NULL;

    return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t* lista){

    if (!lista || lista->cantidad == 0)
        return true;

    return false;
}

size_t lista_elementos(lista_t* lista){

    if (!lista || lista->cantidad == 0 || lista == NULL)
        return 0;    

    return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
    return lista_insertar_en_posicion(lista,elemento,0);
}

int lista_desapilar(lista_t* lista){
    return lista_borrar_de_posicion(lista,0);
}

void* lista_tope(lista_t* lista){
    return lista_elemento_en_posicion(lista,0);
}

int lista_encolar(lista_t* lista, void* elemento){
    return lista_insertar(lista,elemento);
}

int lista_desencolar(lista_t* lista){
    return lista_borrar_de_posicion(lista,0);
}

void* lista_primero(lista_t* lista){
    return lista_elemento_en_posicion(lista,0);
}

void nodo_destruir_todos(nodo_t* nodo){

    if (nodo->siguiente){
        nodo_destruir_todos(nodo->siguiente);
    }
    free(nodo);
}

void lista_destruir(lista_t* lista){
    if (lista && lista != NULL){
        if (lista->nodo_inicio != NULL)
            nodo_destruir_todos(lista->nodo_inicio);
        free(lista);
    }
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){

    if (!lista)
        return NULL;

    lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
    
    iterador->corriente = lista->nodo_inicio;
    iterador->lista = lista;

    return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){

    if (!iterador)
        return false;

    return iterador->corriente != NULL;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){

    if (!iterador || !iterador->lista || !iterador->corriente)
        return false;

    iterador->corriente = iterador->corriente->siguiente;
    if (iterador->corriente != NULL)
        return true;
    return false;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){

    if (iterador != NULL && iterador && iterador->corriente != NULL && iterador->lista != NULL)
        return iterador->corriente->elemento;

    return NULL;
}

void lista_iterador_destruir(lista_iterador_t* iterador){

    if (iterador)
        free(iterador);

}

size_t nodo_con_cada_elemento(nodo_t* nodo, bool (*funcion)(void*, void*), void *contexto){

    if (!nodo)
        return 0;

    if (funcion(nodo->elemento,contexto) && nodo != NULL)
        return 1+nodo_con_cada_elemento(nodo->siguiente,funcion,contexto);

    return 1;
}


size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){

    if(!lista || lista == NULL || !funcion)
        return 0;

    return nodo_con_cada_elemento(lista->nodo_inicio,funcion,contexto);
}
