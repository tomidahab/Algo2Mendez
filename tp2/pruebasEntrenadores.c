#include "pa2mm.h"
#include "src/salon.h"
#include "src/entrenador.h"
#include "src/lista.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIN_ERROR 0
#define ERROR -1

void alCrearUnEntrenador_seCrea(){

    pa2m_afirmar(crear_entrenador(NULL, 10) == NULL,"No se crea un entrenador sin nombre");

    entrenador_t* entrenador = crear_entrenador("Jose", 10);
    pa2m_afirmar(entrenador,"El entrenador se crea");
    pa2m_afirmar(strcmp(obtener_nombre(entrenador),"Jose")== 0, "El nombre es correcto");
    pa2m_afirmar(obtener_victorias(entrenador) == 10, "Las victorias son correctas");
    liberar_entrenador(entrenador);

}

void alCrearUnPokemon_seCrea(){

    pa2m_afirmar(crear_pokemon(NULL, 10, 5, 4, 3, 2) == NULL,"No se crea un pokemon sin nombre");

    pokemon_t* pokemon = crear_pokemon("Pikachu", 10, 5, 4, 3, 2);
    pa2m_afirmar(pokemon,"El pokemon se crea");
    pa2m_afirmar(strcmp(obtener_nombre_pokemon(pokemon),"Pikachu") == 0,"El nombre es correcto");
    pa2m_afirmar(obtener_nivel_pokemon(pokemon) == 10, "El nivel es correcto");
    pa2m_afirmar(obtener_defensa_pokemon(pokemon) == 5, "La defensa es correcta");
    pa2m_afirmar(obtener_fuerza_pokemon(pokemon) == 4, "La fuerza es correcta");
    pa2m_afirmar(obtener_inteligencia_pokemon(pokemon) == 3, "La inteligencia es correcta");
    pa2m_afirmar(obtener_velocidad_pokemon(pokemon) == 2, "La velocidad es correcta");
    free(pokemon);

}

void alAgregarUnPokemonAUnEntrenadorNuloOViceversa_noSeAgrega(){

    entrenador_t* entrenador = crear_entrenador("Jose", 10);
    pa2m_afirmar(agregar_pokemon(entrenador,NULL) ==ERROR, "No se agrega un pokemon nulo");
    pa2m_afirmar(obtener_numero_pokemones(entrenador) == 0,"Un entrenador vacio, no tiene pokemones");
    pokemon_t* pokemon_1 = crear_pokemon("Pikachu", 10, 5, 4, 3, 2);
    pa2m_afirmar(agregar_pokemon(NULL,pokemon_1) == -1, "No se agrega un pokemon a un entrenador nulo");
    pa2m_afirmar(agregar_pokemon(entrenador,pokemon_1) == 0,"Se agrega un pokemon a un entrenador");
    pa2m_afirmar(obtener_pokemon(entrenador,"Pikachu") == pokemon_1,"El pokemon agregado es correcto, y se obtiene correctamente");
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,0) == pokemon_1,"El pokemon se inserta en la posicion correcta, y se obtiene correctamente");
    pa2m_afirmar(obtener_numero_pokemones(entrenador) == 1,"Un entrenador no vacio, tiene un pokemon");
    pa2m_afirmar(sacar_pokemon(entrenador,pokemon_1) == ERROR, "No se puede sacar un pokemon a un entrenador con un pokemon o menos");
    pokemon_t* pokemon_2 = crear_pokemon("Articuno", 10, 5, 4, 3, 2);
    pa2m_afirmar(agregar_pokemon(entrenador,pokemon_2) == 0,"Se agrega un pokemon a un entrenador");
    pa2m_afirmar(obtener_pokemon(entrenador,"Articuno") == pokemon_2,"El pokemon agregado es correcto, y se obtiene correctamente");
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,0) == pokemon_1,"El pokemon se inserta en la posicion correcta, y se obtiene correctamente");
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,1) == pokemon_2,"El otro pokemon queda en la posicion correcta, y se obtiene correctamente");
    pa2m_afirmar(obtener_numero_pokemones(entrenador) == 2,"Un entrenador vacio, tiene 2 pokemones");
    pa2m_afirmar(sacar_pokemon(entrenador,pokemon_1) == SIN_ERROR, "Se puede sacar un pokemon a un entrenador con dos pokemon o mas");
    pa2m_afirmar(obtener_pokemon(entrenador,"Articuno") == pokemon_2,"Al sacar un pokemon, el otro queda como estaba");
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,0) == pokemon_2,"El pokemon que no se saco, queda en la posicion correcta");
    pa2m_afirmar(obtener_numero_pokemones(entrenador) == 1,"El entrenador queda con un pokemon menos que antes");
    pokemon_t* pokemon_3 = crear_pokemon("Abra", 3, 3, 3, 3, 1);
    pa2m_afirmar(agregar_pokemon(entrenador,pokemon_3) == 0,"Se agrega otro pokemon a un entrenador");
    pa2m_afirmar(obtener_pokemon(entrenador,"Abra") == pokemon_3,"El pokemon agregado es correcto, y se obtiene correctamente");
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,0) == pokemon_2,"El otro pokemon queda en la posicion correcta, y se obtiene correctamente");
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,1) == pokemon_3,"El pokemon se inserta en la posicion correcta, y se obtiene correctamente");
    pokemon_t* pokemon_4 = crear_pokemon("Magikarp", 1, 1, 1, 1, 1);
    pa2m_afirmar(agregar_pokemon(entrenador,pokemon_4) == 0,"Se agrega otro pokemon a un entrenador");
    pa2m_afirmar(obtener_pokemon(entrenador,"Magikarp") == pokemon_4,"El pokemon agregado es correcto, y se obtiene correctamente");
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,0) == pokemon_2,"El otro pokemon queda en la posicion correcta, y se obtiene correctamente"); 
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,1) == pokemon_3,"El otro pokemon queda en la posicion correcta, y se obtiene correctamente");
    pa2m_afirmar(obtener_pokemon_con_posicion(entrenador,2) == pokemon_4,"El pokemon se inserta en la posicion correcta, y se obtiene correctamente");   


    liberar_entrenador(entrenador);
}

int main(){
    pa2m_nuevo_grupo("PRUEBAS DE ENTRENADOR");
    pa2m_nuevo_grupo("Pruebas de crear");
    alCrearUnEntrenador_seCrea();
    alCrearUnPokemon_seCrea();

    pa2m_nuevo_grupo("Pruebas de agregar, obtener y quitar");
    alAgregarUnPokemonAUnEntrenadorNuloOViceversa_noSeAgrega();
   
    return pa2m_mostrar_reporte();
}