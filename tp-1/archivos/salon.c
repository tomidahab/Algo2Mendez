#include "salon.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_NOMBRE_POKEMON    10
#define MAX_NOMBRE_ENTRENADOR 30
#define FORMATO_ESCRITURA_ENTRENADOR  "%s;%i\n"
#define FORMATO_ESCRITURA_POKEMON     "%s;%i;%i;%i;%i;%i\n"

entrenador_t** ordenar_entrenadores(entrenador_t** vector_entrenadores){
    entrenador_t* entrenador_aux;
    size_t cantidad_entrenadores = vtrlen(vector_entrenadores);
    int i;
    int k;
    for(i = 0; i< cantidad_entrenadores; i++){
        for(k = 0;k<cantidad_entrenadores;k++){
            if(vector_entrenadores[k]->victorias > vector_entrenadores[i]->victorias){
                entrenador_aux = vector_entrenadores[i];
                vector_entrenadores[i] = vector_entrenadores[k];
                vector_entrenadores[k] = entrenador_aux;     
            }    
        }
    }
    return vector_entrenadores;
}


salon_t* salon_leer_archivo(const char* nombre_archivo){
    salon_t* salon = malloc(sizeof(salon_t));
    if(!salon){
        vtrfree(salon);
        return NULL;
    }
    else{
        memset(salon, 0, sizeof(salon_t));
    }
	FILE* archivo_lectura = fopen(nombre_archivo,"r");
    if (!archivo_lectura){
        vtrfree(salon);
        return NULL;
    }
    char* linea = fgets_alloc(archivo_lectura);
    char** vector_a_guardar = split(linea, ';');
    //int numero_de_entrenadores = 0;
    //int numero_de_pokemones_en_equipo = 0;
    entrenador_t** vector_entrenadores = NULL;
    //pokemon_t** vector_pokemones = NULL;
    //entrenador_t* vector_entrenador_actual = NULL;
    entrenador_t* entrenador_actual = NULL;
    pokemon_t* pokemon_actual = NULL;
    //entrenador_actual->equipo = NULL;
    size_t longitud_nombre;
    size_t i;
    while (vector_a_guardar){
        longitud_nombre = strlen(vector_a_guardar[0]);
        if (vtrlen(vector_a_guardar) == 2){
            entrenador_actual = malloc(sizeof(entrenador_t));
            if (!entrenador_actual)
                return NULL;
            else{
                memset(entrenador_actual, 0, sizeof(entrenador_t));
            }
            entrenador_actual->victorias = atoi(vector_a_guardar[1]);
            for (i=0;i<longitud_nombre;i++){
                entrenador_actual->nombre[i] = vector_a_guardar[0][i];      
            }
        }
        else{
            pokemon_actual = malloc(sizeof(pokemon_t));
            if (!pokemon_actual)
                return NULL;
            else{
                memset(pokemon_actual, 0, sizeof(pokemon_t));
            }
            for (i=0;i<longitud_nombre;i++){
                pokemon_actual->nombre[i] = vector_a_guardar[0][i];      
            }
            pokemon_actual->nivel = atoi(vector_a_guardar[1]);
            pokemon_actual->defensa = atoi(vector_a_guardar[2]);
            pokemon_actual->fuerza = atoi(vector_a_guardar[3]);
            pokemon_actual->inteligencia = atoi(vector_a_guardar[4]);
            pokemon_actual->velocidad = atoi(vector_a_guardar[5]);
            entrenador_actual->equipo = vtradd(entrenador_actual->equipo,pokemon_actual);
        }
        free(linea);
        vtrfree(vector_a_guardar);
        linea = fgets_alloc(archivo_lectura);
        vector_a_guardar = split(linea, ';');
        if (vtrlen(vector_a_guardar) == 2 || !vector_a_guardar){
            vector_entrenadores = vtradd(vector_entrenadores, entrenador_actual);
            //entrenador_actual->equipo = NULL;
            entrenador_actual = NULL;
            pokemon_actual = NULL;        
        }
    }  
    free(linea);
    vtrfree(vector_a_guardar);
    salon->entrenadores = vector_entrenadores;
    fclosen(archivo_lectura);
    return salon;
}

int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    FILE* archivo_escritura = fopen(nombre_archivo,"w");
    if (!archivo_escritura)
        return -1;
    size_t numero_de_entrenadores = vtrlen(salon->entrenadores);
    if (numero_de_entrenadores == 0)
        return -1;
    size_t numero_de_pokemones;
    int i;
    int j;
    char* nombre_a_escribir;
    for(i = 0; i < numero_de_entrenadores; i++){
        nombre_a_escribir = salon->entrenadores[i]->nombre;
        fprintf(archivo_escritura,FORMATO_ESCRITURA_ENTRENADOR,nombre_a_escribir,salon->entrenadores[i]->victorias);
        numero_de_pokemones = vtrlen(salon->entrenadores[i]->equipo);
        for(j = 0; j < numero_de_pokemones;j++){
            fprintf(archivo_escritura,FORMATO_ESCRITURA_POKEMON,salon->entrenadores[i]->equipo[j]->nombre,salon->entrenadores[i]->equipo[j]->nivel,salon->entrenadores[i]->equipo[j]->defensa,salon->entrenadores[i]->equipo[j]->fuerza,salon->entrenadores[i]->equipo[j]->inteligencia,salon->entrenadores[i]->equipo[j]->velocidad);
        }      
    }
    fclosen(archivo_escritura);
    return (int)numero_de_entrenadores;
}

salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon || !entrenador)
        return NULL;
    entrenador_t** aux = vtradd(salon->entrenadores,entrenador);
    if(!aux){
        free(aux);
        return NULL;
    }
    aux = ordenar_entrenadores(aux);
    salon->entrenadores = aux;    
    return salon;
}

entrenador_t** salon_obtener_entrenadores_mas_ganadores(salon_t* salon, int cantidad_minima_victorias){
    if(!salon)
        return NULL;
    if(cantidad_minima_victorias == 0)
        return salon->entrenadores;    
    entrenador_t** vector_entrenadores = NULL;
    entrenador_t* entrenador_actual = NULL;
    size_t cantidad_entrenadores = vtrlen(salon->entrenadores);
    int i;
    for(i = 0;i<cantidad_entrenadores;i++){
        entrenador_actual = salon->entrenadores[i];
        if(entrenador_actual->victorias >= cantidad_minima_victorias)
            vector_entrenadores = vtradd(vector_entrenadores,entrenador_actual);
    }
        
    return vector_entrenadores;
}

void salon_mostrar_entrenador(entrenador_t* entrenador){
    if (entrenador){
        size_t cantidad_pokemones = vtrlen(entrenador->equipo);
        int i;
        printf("%s cuenta con %i victorias y los siguientes pokemones:\n",entrenador->nombre,entrenador->victorias);
        if (cantidad_pokemones == 0)
            printf("El entrenador no cuenta con pokemones\n");
        else{
            for(i = 0; i<cantidad_pokemones;i++){
                printf("%i. %s tiene nivel %i, %i defensa, %i fuerza, %i inteligencia y %i velocidad\n", i+1,entrenador->equipo[i]->nombre,entrenador->equipo[i]->nivel,entrenador->equipo[i]->defensa,entrenador->equipo[i]->fuerza,entrenador->equipo[i]->inteligencia,entrenador->equipo[i]->velocidad);
            }        
        }
            
    }
}


void salon_destruir(salon_t* salon){
    size_t cantidad_entrenadores = vtrlen(salon->entrenadores);
    size_t cantidad_pokemones;
    int i;
    for(i = 0; i < cantidad_entrenadores; i++){
        cantidad_pokemones = vtrlen(salon->entrenadores[i]->equipo);
        if (cantidad_pokemones > 0)
            vtrfree(salon->entrenadores[i]->equipo);    
    }
    if (salon->entrenadores)
        vtrfree(salon->entrenadores);
    free(salon);
}
