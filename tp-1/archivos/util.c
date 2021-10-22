#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

size_t vtrlen(void* ptr){
    
    //void* vector = (void**)ptr;vector
    if (ptr == NULL){
        return 0;
    }
    size_t longitud = 0;
    while (((void**)ptr)[longitud]){
        longitud++;
    }
    return (longitud);
}

void* vtradd(void* ptr, void* item){
    void** puntero = (void**)ptr;
    //Saca la longitud del nuevo vector SIN el NULL
    size_t longitud = (vtrlen(puntero)) + 1;
    //Aca tiene en cuenta el NULL cuando le suma 1 a longitud
    void** ptr_nuevo = realloc(puntero, (longitud + 1) * sizeof(void*));
    if (!ptr_nuevo){
        return NULL;
    }
    ptr_nuevo[longitud - 1] = item;
    ptr_nuevo[longitud] = NULL;
    
    return ptr_nuevo;
}

void vtrfree(void* ptr){
    if (!ptr)
        return;
    size_t longitud = vtrlen(ptr);
    void** aux = ptr;
    int i;
    for(i = 0; i < longitud; i++){
        if (aux[i] != NULL)
            free(aux[i]);
    }
    free(ptr);
}

char** split(const char* str, char separador){
    
    if (!str || str == NULL)
        return NULL;
    size_t posicion_inicial = 0;
    size_t posicion_final = 0;
    size_t cantidad_palabras = 1;   
    size_t tamanio;
    char caracter_actual = str[posicion_inicial];
    char* palabra = NULL;
    char** ptr = NULL;
    size_t i;
    size_t j;
    size_t k;
    size_t len_str = strlen(str);
    if (len_str == 0)
        return NULL;
    for(i = 0; i < len_str;i++){
        if (str[i] == separador){
            cantidad_palabras++;      
        }
    }
    for(j = 0; j < cantidad_palabras;j++){
        caracter_actual = str[posicion_inicial];
        while (caracter_actual != separador && caracter_actual){           
            posicion_final++;;
            caracter_actual = str[posicion_final];
        }
        tamanio = posicion_final - posicion_inicial;
        caracter_actual = str[posicion_inicial];
        palabra = malloc(sizeof(char)*(tamanio + 1));
        for(k = 0; k < tamanio; k++){
            caracter_actual = str[k + posicion_inicial];
            palabra[k] = caracter_actual;
        }
        caracter_actual = '\0';
        palabra[tamanio] = caracter_actual;
        ptr = vtradd(ptr,palabra);
        palabra = NULL;
        posicion_final++;
        posicion_inicial = posicion_final;
    }
    
    return ptr;
}

char* fgets_alloc(FILE* archivo){
    size_t tamanio = 512;
    size_t bytes_contados = 0;
    char* str = malloc(tamanio * sizeof(char));

    if (!str)
        return NULL;
    while (fgets(str + bytes_contados, (int)tamanio - (int)bytes_contados, archivo)){
        size_t leidos = strlen(str + bytes_contados);
        if (leidos > 0 && *(str + bytes_contados + leidos -1) == '\n'){
            return str;
        } else {
            char* aux = realloc(str,  tamanio*2);
            if(!aux) {
                free(str);
                return NULL;
            }
            str = aux;
            tamanio *= 2;
        }
        bytes_contados += leidos;
    }    
    if(!bytes_contados){
        free(str);
        return NULL;
    }
    return str;
}

void fclosen(FILE* archivo){
    fclose(archivo);
}
