#ifndef ENTRENADOR_H_
#define ENTRENADOR_H_

#include <stdlib.h>
#include "lista.h"
#include <stdbool.h>

typedef struct _pokemon_t pokemon_t;

typedef struct _entrenador_t entrenador_t;

//Crea un entrenador y reserva la memoria y devuelve un puntero al entrenador o NULL si falla
entrenador_t* crear_entrenador(char* nombre, int victorias);

//Crea un pokemon reservando la memoria correspondiente y devuelve un puntero al pokemon o NULL si falla
pokemon_t* crear_pokemon(char* nombre, int nivel,int defensa, int fuerza, int inteligencia, int velocidad);

//Asigna un pokemon a un a un entrenador, devuelve 0 si se pudo, -1 sino
int agregar_pokemon(entrenador_t* entrenador,pokemon_t* pokemon);

//Saca a un pokemon del equipo de su entrenador y libera su memoria, devuelve 0 si se pudo, -1 sino. Tener en cuenta que no se le puede quitar un pokemon a un entrenador que tiene solo un pokemon.
int sacar_pokemon(entrenador_t* entrenador,pokemon_t* pokemon);

//Devuelve un pokemon a partir de su nombre
pokemon_t* obtener_pokemon(entrenador_t* entrenador, char* nombre_pokemon);

//Devuelve un pokemon a partir de su posicion
pokemon_t* obtener_pokemon_con_posicion(entrenador_t* entrenador, size_t posicion);

//Obiene el nombre de un entrenador
char* obtener_nombre(entrenador_t* entrenador);

//Obtiene las victorias de un entrenador
int obtener_victorias(entrenador_t* entrenador);

//Obtiene el numero de pokemones que tiene un entrenador. Devuelve 0 si no hay o hay algun error
size_t obtener_numero_pokemones(entrenador_t* entrenador);

//Devuelve el nombre de un pokemon
char* obtener_nombre_pokemon(pokemon_t* pokemon);

//Devuelve el nivel de un pokemon
int obtener_nivel_pokemon(pokemon_t* pokemon);

//Devuelve la fuerza de un pokemon
int obtener_fuerza_pokemon(pokemon_t* pokemon);

//Devuelve la defensa de un pokemon
int obtener_defensa_pokemon(pokemon_t* pokemon);

//Devuelve la inteligencia de un pokemon
int obtener_inteligencia_pokemon(pokemon_t* pokemon);

//Devuelve la velocidad de un pokemon
int obtener_velocidad_pokemon(pokemon_t* pokemon);

//Libera a un entrenador y a todos sus pokemones
void liberar_entrenador(entrenador_t* entrenador);

#endif // ENTRENADOR_H_
