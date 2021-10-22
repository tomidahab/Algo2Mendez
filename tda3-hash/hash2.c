#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "hash.h"
#define ERROR -1
#define SIN_ERROR 0
#define VALOR_SOBREESCRITO 1

typedef struct par{

    const char* clave;
    void* elemento;
    bool fue_ocupado;

}par_t;

struct hash{

    par_t** tabla;

    size_t capacidad_maxima;
    size_t entradas_ocupadas;

    hash_destruir_dato_t destructor;

};


size_t funcion_hash(const char* str, size_t capacidad_maxima){

    size_t longitud_string = strlen(str);
    if (longitud_string == 0)
        return longitud_string;

    size_t hash = longitud_string * str[longitud_string-1] + 31*str[0] + 7*str[longitud_string/2] - 1;
    return hash % capacidad_maxima;
}

void mostrar_hash(hash_t* hash,char* str){  //Esta es una funcion que use para testear un par de cosas que se me complicaron

    par_t* par_actual;
    size_t elemento_actual;
    size_t i;

    printf("%s\n",str);

    for(i = 0; i < hash->capacidad_maxima;i++){

        par_actual = *(hash->tabla + i);

        if(par_actual){
            if(par_actual->clave){
                elemento_actual = *((int*)par_actual->elemento);
                printf("%li. Clave: %s | Elemento: %li\n",i+1, par_actual->clave,elemento_actual);
            }
            else{
                printf("%li. Vacio, pero estuvo ocupado",i+1);
            }
        }
        else
            printf("%li.\n", i+1);

    }
    printf("\n");


}

hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad_inicial){

    if (capacidad_inicial <= 3)
        capacidad_inicial = 3;

    hash_t* hash = malloc(sizeof(hash_t));
    if(!hash)
        return NULL;


    hash->capacidad_maxima = capacidad_inicial;
    hash->entradas_ocupadas = 0;
    hash->destructor = destruir_elemento;

    hash->tabla = calloc(capacidad_inicial,sizeof(par_t*));
    if(!hash->tabla){
        free(hash);
        return NULL;
    }
    int i;
    int j;
    for (i = 0; i < capacidad_inicial; i++){
        hash->tabla[i] = calloc(1,sizeof(par_t));
        if(!hash->tabla[i]){
            for (j = 0; j < i; j++){
                free(hash->tabla[j]);
            }
            free(hash->tabla);
            free(hash);
        }
    }

    return hash;
}

int tabla_insertar(par_t** tabla,const char* clave, void* elemento, size_t capacidad_maxima,hash_destruir_dato_t destructor){

    if(!tabla || !clave)
        return ERROR;

    size_t valor_hash = funcion_hash(clave,capacidad_maxima);

    par_t* par_actual = *(tabla + valor_hash);
    while(par_actual != NULL){
        if(par_actual->clave){
            if(strcmp(par_actual->clave,clave) == 0){
                par_actual->clave = clave;
                par_actual->elemento = elemento;
                return VALOR_SOBREESCRITO; //Si devuelve VALOR_SOBREESCRITO esta funcion, yo se que se sobreescribio algo, por lo cual no voy a sumarle uno a entradas_ocupadas
            }

            valor_hash++;

            if(valor_hash >= capacidad_maxima)
                valor_hash = 0;

            par_actual = *(tabla + valor_hash);
        }
        else{
            par_actual->clave = clave;
            par_actual->elemento = elemento;
            return SIN_ERROR;
        }

    }
    par_actual->clave = clave;
    par_actual->elemento = elemento;

    return SIN_ERROR;
}

void tabla_destruir(par_t** tabla,size_t capacidad_maxima, hash_destruir_dato_t destructor){

    size_t i;
    par_t* par_actual;
    for(i = 0; i < capacidad_maxima;i++){
        par_actual = *(tabla + i);
        if(par_actual){
            if(destructor && par_actual->elemento)
                destructor(par_actual->elemento);
            
            free(par_actual);
        }
    }
    free(tabla);
    return;
}

int rehash(hash_t* hash, size_t capacidad_nueva){

    size_t i;

    par_t** tabla_nueva = calloc(capacidad_nueva,sizeof(par_t*));

    if(!tabla_nueva)
        return ERROR;

    par_t* par_actual;

    for(i = 0; i < hash->capacidad_maxima;i++){
        par_actual = *(hash->tabla + i);
        if(par_actual){
            if(par_actual->clave){
                tabla_insertar(tabla_nueva,par_actual->clave,par_actual->elemento,capacidad_nueva,hash->destructor);
            }
        }
    }
    tabla_destruir(hash->tabla,hash->capacidad_maxima,NULL);
    hash->tabla = tabla_nueva;
    hash->capacidad_maxima = capacidad_nueva;
    return SIN_ERROR;
}

int hash_insertar(hash_t* hash, const char* clave, void* elemento){

    if(!clave || !hash)
        return ERROR;
    
    int devuelto = tabla_insertar(hash->tabla,clave,elemento,hash->capacidad_maxima,hash->destructor);

    if(devuelto == ERROR)
        return ERROR;

    if(devuelto == SIN_ERROR)
        hash->entradas_ocupadas++; //Esto unicamente cuando se agrega un par, cuando se sobreescribe no lo hace xq devuelto va a ser 1


    //mostrar_hash(hash,"ANTES REHASH"); //Esto lo hice xq me vino bien tener alguna manera de visualizar el hash
    if(hash->capacidad_maxima/2 <= hash->entradas_ocupadas)
        return rehash(hash, hash->capacidad_maxima * 2);

    //mostrar_hash(hash,"DESPUES REHASH");

    return SIN_ERROR;
    
}

int hash_quitar(hash_t* hash, const char* clave){

    if(!hash || !clave)
        return ERROR;

    size_t valor_hash = funcion_hash(clave,hash->capacidad_maxima);
    bool salir_loop = false;

    par_t* par_actual = *(hash->tabla + valor_hash);

    while(par_actual != NULL && salir_loop == false){

        if(par_actual->clave){
            if(strcmp(par_actual->clave,clave) == 0)
                salir_loop = true;
            else{
                valor_hash++;

                if(valor_hash >= hash->capacidad_maxima)
                    valor_hash = 0;

                par_actual = *(hash->tabla + valor_hash);
            }
        }
        else{
            valor_hash++;

            if(valor_hash >= hash->capacidad_maxima)
                valor_hash = 0;

            par_actual = *(hash->tabla + valor_hash);
        }
    }
       
    if(par_actual == NULL){
        return ERROR;
    }
    else{
        par_actual->clave = NULL;
        par_actual->elemento = NULL;
        hash->entradas_ocupadas--;
    }
    return SIN_ERROR;
}

void* hash_obtener(hash_t* hash, const char* clave){

    if(!hash || !clave){
        return NULL;
    }

    size_t valor_hash = funcion_hash(clave,hash->capacidad_maxima);

    par_t* par_actual = *(hash->tabla + valor_hash);

    while(par_actual != NULL){

        if(par_actual->clave){
            if(strcmp(par_actual->clave,clave) == 0)
            return par_actual->elemento;
        }
        valor_hash++;

        if(valor_hash >= hash->capacidad_maxima)
            valor_hash = 0;

        par_actual = *(hash->tabla + valor_hash);
    }
    return NULL;
}

size_t hash_cantidad(hash_t* hash){
    if(!hash)
        return 0;

    return hash->entradas_ocupadas;
}

bool hash_contiene(hash_t* hash, const char* clave){

    void* elemento = hash_obtener(hash,clave);

    if(!elemento)
        return false;

    return true;
}

void hash_destruir(hash_t* hash){
    if(!hash){
        return;
    }
    if(hash->tabla)
        tabla_destruir(hash->tabla,hash->capacidad_maxima,hash->destructor);
    
    free(hash);
    return;
}

size_t hash_con_cada_clave(hash_t* hash, bool (*funcion)(hash_t* hash, const char* clave, void* aux), void* aux){

    if(!hash || !funcion)
        return 0;

    size_t i;
    size_t contador = 0;
    par_t* par_actual;
    bool devuelto;

    for(i = 0; i < hash->capacidad_maxima; i++){

        par_actual = *(hash->tabla + i);
        
        if(par_actual){
            if(par_actual->clave){
                devuelto = funcion(hash,par_actual->clave,aux);
                contador++;
                if(devuelto)
                    return contador;
            }
        }
    }
    return contador;
}
