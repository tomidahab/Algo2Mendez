#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include "entrenador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NOMBRE_ENTRENADOR 30
#define MAX_NOMBRE_POKEMON    20
#define SIN_ERROR 0
#define ERROR -1

struct _pokemon_t{
    char nombre[MAX_NOMBRE_POKEMON];
    int nivel;
    int fuerza;
    int inteligencia;
    int velocidad;
    int defensa;
};

struct _entrenador_t{

    char nombre[MAX_NOMBRE_ENTRENADOR];
    int victorias;
    lista_t* pokemones;

};

//Crea un entrenador, si se puede devuelve el pokemon, sino devuelve NULL
entrenador_t* crear_entrenador(char* nombre, int victorias){
    if(!nombre)
        return NULL;

    entrenador_t* entrenador = calloc(1,sizeof(entrenador_t));
    if (!entrenador)
        return NULL;

    entrenador->pokemones = lista_crear();
    if(!entrenador->pokemones){
        free(entrenador);
        return NULL;
    }
    strcpy(entrenador->nombre,nombre);
    entrenador->victorias = victorias;
    return entrenador;
}

//Crea un pokemon, si se puede devuelve el pokemon, sino devuelve NULL
pokemon_t* crear_pokemon(char* nombre, int nivel,int defensa, int fuerza, int inteligencia, int velocidad){
    if(!nombre)
        return NULL;

    pokemon_t* pokemon = malloc(sizeof(pokemon_t));
    if(!pokemon)
        return NULL;

    strcpy(pokemon->nombre,nombre);
    pokemon->nivel = nivel;
    pokemon->fuerza = fuerza;
    pokemon->inteligencia = inteligencia;
    pokemon->velocidad = velocidad;
    pokemon->defensa = defensa;
    return pokemon;
}

//Agrega un pokemon. Si se puede devuelve 0, sino -1
int agregar_pokemon(entrenador_t* entrenador,pokemon_t* pokemon){
    if(!entrenador || !pokemon)
        return ERROR;

    return lista_insertar(entrenador->pokemones,pokemon);
}

//Devuelve false si algun pokemon es nulo o si no son iguales, si son iguales devuelve true
bool pokemones_son_iguales(void* _pokemon1, void* _pokemon2){
    pokemon_t* pokemon1 = (pokemon_t*)_pokemon1;
    pokemon_t* pokemon2 = (pokemon_t*)_pokemon2;

    if(!pokemon1 || !pokemon2)
        return false;
    if(strcmp(pokemon1->nombre,pokemon2->nombre) == 0 && pokemon1->nivel == pokemon2->nivel && pokemon1->defensa == pokemon2->defensa && pokemon1->fuerza == pokemon2->fuerza && pokemon1->inteligencia == pokemon2->inteligencia && pokemon1->velocidad == pokemon2->velocidad){
        return true;
    }
    return false;
}

//Saca un pokemon del equipo de un entrenador, devuelve 0 si pudo, -1 sino pudo, o si ese pokemon no esta en el equipo del entrenador
int sacar_pokemon(entrenador_t* entrenador, pokemon_t* pokemon){
    if(!entrenador || !pokemon)
        return ERROR;

    if(lista_elementos(entrenador->pokemones) <= 1)
        return ERROR;

    size_t posicion_actual = 0;
    pokemon_t* pokemon_actual = lista_elemento_en_posicion(entrenador->pokemones,posicion_actual);
    while(pokemon_actual){
        if(pokemones_son_iguales(pokemon_actual,pokemon)){
           int devuelto = lista_borrar_de_posicion(entrenador->pokemones,posicion_actual);
           free(pokemon_actual);
           return devuelto;
        }
        posicion_actual++;
        pokemon_actual = lista_elemento_en_posicion(entrenador->pokemones,posicion_actual);
    }
    return ERROR;
}

//Obtiene un pokemon en base a su nombre, devuelve un puntero al pokemon o null si no lo encontro
pokemon_t* obtener_pokemon(entrenador_t* entrenador, char* nombre_pokemon){
    if(!entrenador || !nombre_pokemon)
        return NULL;

    if(lista_elementos(entrenador->pokemones) == 0)
        return NULL;

    size_t posicion_actual = 0;
    pokemon_t* pokemon_actual = lista_elemento_en_posicion(entrenador->pokemones,posicion_actual);
    while(pokemon_actual){
        if(strcmp(pokemon_actual->nombre,nombre_pokemon) == 0)
            return pokemon_actual;
        posicion_actual++;
        pokemon_actual = lista_elemento_en_posicion(entrenador->pokemones,posicion_actual);
    }
    return NULL;
}

//Devuelve el pokemon en cierta posicion de un entrenador
pokemon_t* obtener_pokemon_con_posicion(entrenador_t* entrenador, size_t posicion){
    return lista_elemento_en_posicion(entrenador->pokemones,posicion);
}

char* obtener_nombre(entrenador_t* entrenador){
    if(!entrenador)
        return NULL;

    return entrenador->nombre;
}

int obtener_victorias(entrenador_t* entrenador){
    if(!entrenador)
        return ERROR;

    return entrenador->victorias;
}

char* obtener_nombre_pokemon(pokemon_t* pokemon){
    if(!pokemon)
        return NULL;

    return pokemon->nombre;
}

int obtener_nivel_pokemon(pokemon_t* pokemon){
    if(!pokemon)
        return -1;

    return pokemon->nivel;
}

int obtener_fuerza_pokemon(pokemon_t* pokemon){
    if(!pokemon)
        return -1;

    return pokemon->fuerza;
}

int obtener_inteligencia_pokemon(pokemon_t* pokemon){
    if(!pokemon)
        return -1;

    return pokemon->inteligencia;
}

int obtener_defensa_pokemon(pokemon_t* pokemon){
    if(!pokemon)
        return -1;

    return pokemon->defensa;
}

int obtener_velocidad_pokemon(pokemon_t* pokemon){
    if(!pokemon)
        return -1;

    return pokemon->velocidad;
}

size_t obtener_numero_pokemones(entrenador_t* entrenador){
    if(!entrenador)
        return 0;

    return lista_elementos(entrenador->pokemones);
}

bool borrar_pokemon(void* _pokemon,void* extra){
    extra++;
    pokemon_t* pokemon = (pokemon_t*)_pokemon;
    if(!pokemon)
        return false;
    free(pokemon);
    return true;
}

void liberar_entrenador(entrenador_t* entrenador){
    if(entrenador){
        lista_con_cada_elemento(entrenador->pokemones,borrar_pokemon,NULL);
        lista_destruir(entrenador->pokemones);
        free(entrenador);
    }
}