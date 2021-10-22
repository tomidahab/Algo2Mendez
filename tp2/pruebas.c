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

bool tiene_mas_de_extra_victorias(entrenador_t* entrenador, void* extra){

    int minimo_victorias = *(int*)extra;

    if(obtener_victorias(entrenador) > minimo_victorias)
        return true;

    return false;
}

void alLeerUnSalonNulo_noSeLee(){
    salon_t* salon1 = salon_leer_archivo("src/archivos_prueba/asdasdasdasdasdasdasd.asd");

    pa2m_afirmar(salon1 == NULL, "Leer un archivo inexistente devuelve un salon nulo.");

    salon_t* salon2 = salon_leer_archivo("src/archivos_prueba/salon_con_entrenadores_duplicados.txt");

    pa2m_afirmar(salon2 == NULL, "Leer un archivo con un entrenador duplicado devuelve un salon nulo.");

    salon_destruir(salon1);
    salon_destruir(salon2);
}

void alLeerUnSalonConUnEntrenadorYUnPokemon_SeLee(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("src/archivos_prueba/salon_1e_1p.txt")) != NULL, "Puedo leer un archivo con 1 entrenador y 1 pokemon");

    int cero = 0;
    lista_t* lista_devuelta_1 = salon_filtrar_entrenadores(salon,tiene_mas_de_extra_victorias,&cero);

    pa2m_afirmar(lista_elementos(lista_devuelta_1) == 1,"Al pedirle que filtre entrenadores la lista devuelta tiene la cantidad de elementos correcto");
    pa2m_afirmar(strcmp(obtener_nombre(lista_elemento_en_posicion(lista_devuelta_1,0)),"entrenador1") == 0,"El nombre del primer entrenador es correcto");
    lista_destruir(lista_devuelta_1);

    pa2m_afirmar((salon_guardar_archivo(salon,"src/archivos_prueba/salon_1e_1p_actualizado.txt")) == 1, "Pudo guardar un salon con 1 entrenador y 1 pokemon");

    salon_destruir(salon);
}

void alLeerUnSalonConTresEntrenadoresSinPokemon_SeLee(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("src/archivos_prueba/salon_3e.txt")) == NULL, "No puedo leer un archivo con 3 entrenadores sin pokemon");

    salon_destruir(salon);
}

void alLeerUnSalonConDosEntrenadoresYDosPokemones_SeLee(){
    salon_t* salon = NULL;

    pa2m_afirmar((salon = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt")) != NULL, "Puedo leer un archivo con 2 entrenadores y 2 pokemon cada uno");

    if(!salon)
        return;

    int cero = 0;
    lista_t* lista_devuelta_1 = salon_filtrar_entrenadores(salon,tiene_mas_de_extra_victorias,&cero);

    pa2m_afirmar(lista_elementos(lista_devuelta_1) == 2,"Al pedirle que filtre entrenadores la lista devuelta tiene la cantidad de elementos correcto");
    pa2m_afirmar(strcmp(obtener_nombre(lista_elemento_en_posicion(lista_devuelta_1,0)),"entrenador1") == 0,"El nombre del primer entrenador es correcto");
    pa2m_afirmar(strcmp(obtener_nombre(lista_elemento_en_posicion(lista_devuelta_1,1)),"entrenador2") == 0,"El nombre del segundo entrenador es correcto");
    lista_destruir(lista_devuelta_1);

    pa2m_afirmar((salon_guardar_archivo(salon,"src/archivos_prueba/salon_2e_2p_actualizado.txt")) == 2, "Pudo guardar un salon con 2 entrenadores");

    salon_destruir(salon);
}

void alAgregarUnEntrenadorAUnSalon_SeAgregaCorrectamente(){

    salon_t* salon = NULL;

    salon = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt");

    if(!salon)
        return;

    entrenador_t* entrenador = crear_entrenador("Jose", 10);

    if(!entrenador)
        return;

    pokemon_t* pokemon_1 = crear_pokemon("Pikachu", 10, 5, 4, 3, 2);

    if(!pokemon_1)
        return;

    if(agregar_pokemon(entrenador,pokemon_1) == ERROR){
        free(pokemon_1);
        liberar_entrenador(entrenador);
        salon_destruir(salon);
    }

    pa2m_afirmar(salon_agregar_entrenador(NULL,entrenador) == NULL,"Al tratar de agregar un entrenador a un salon nulo, no se agrega");
    pa2m_afirmar(salon_agregar_entrenador(salon,NULL) == NULL,"Al tratar de agregar un entrenador nulo a un salon , no se agrega");
    pa2m_afirmar(salon_agregar_entrenador(salon,entrenador) == salon,"Al tratar de agregar un entrenador a un salon se agrega correctamente");

    salon_destruir(salon);

}

void alFiltrarEntrenadoresPorSusVictorias_seFiltranCorrectamente(){

    salon_t* salon = NULL;

    salon = salon_leer_archivo("src/archivos_prueba/salon_3e.txt");

    if(!salon)
        return;

    entrenador_t* entrenador = crear_entrenador("Jose", 10);

    if(!entrenador)
        return;

    pokemon_t* pokemon_1 = crear_pokemon("Pikachu", 10, 5, 4, 3, 2);

    if(!pokemon_1)
        return;

    if(agregar_pokemon(entrenador,pokemon_1) == ERROR){
        free(pokemon_1);
        liberar_entrenador(entrenador);
        salon_destruir(salon);
        return;
    }
    salon = salon_agregar_entrenador(salon,entrenador);
    if(!salon){
        salon_destruir(salon);
        return;
    }
    int uno = 1;
    int mil = 1000;
    lista_t* lista_devuelta_1 = salon_filtrar_entrenadores(salon,tiene_mas_de_extra_victorias,&uno);
    pa2m_afirmar(lista_elementos(lista_devuelta_1) == 3,"La lista devuelta tiene la cantidad de elementos correcto");
    pa2m_afirmar(strcmp(obtener_nombre(lista_elemento_en_posicion(lista_devuelta_1,0)),"Azul") == 0,"El nombre del primer entrenador es correcto");
    pa2m_afirmar(strcmp(obtener_nombre(lista_elemento_en_posicion(lista_devuelta_1,1)),"Jose") == 0,"El nombre del segundo entrenador es correcto");
    pa2m_afirmar(strcmp(obtener_nombre(lista_elemento_en_posicion(lista_devuelta_1,2)),"Yony") == 0,"El nombre del tercer entrenador es correcto");
    lista_destruir(lista_devuelta_1);
    lista_t* lista_devuelta_2 = salon_filtrar_entrenadores(salon,tiene_mas_de_extra_victorias,&mil);
    pa2m_afirmar(lista_elementos(lista_devuelta_2) == 0,"Si no cumple ningun entrenador, devuelve una lista vacia");
    lista_destruir(lista_devuelta_2);
    salon_destruir(salon);
}

void alTratarDeInterpretarUnComandoInvalido_devuelveNull(){

    salon_t* salon = salon_leer_archivo("src/archivos_prueba/salon_3e.txt");

    if(!salon)
        return;

    char* devuelto = salon_ejecutar_comando(salon,"SAIDWH:jsjjs,qw");

    pa2m_afirmar(devuelto == NULL,"Al tratar de ejecutar un comando no valido no se ejecuta");

    if(devuelto)
        free(devuelto);

    salon_destruir(salon);

}

void alTratarDeInterpretarUnComandoENTRENADORES_devuelveElStringCorrecto(){

    salon_t* salon = salon_leer_archivo("src/archivos_prueba/salon_3e.txt");

    if(!salon)
        return;

    char* devuelto = salon_ejecutar_comando(salon,"ENTRENADORES");

    pa2m_afirmar(devuelto != NULL,"Al tratar de ejecutar el comando ENTRENADORES, se ejecuta");
    pa2m_afirmar(strcmp(devuelto,"Azul,2\nJuan,1\nYony,3\n") == 0,"La string devuelta es correcta");

    if(devuelto)
        free(devuelto);

    salon_destruir(salon);

}

void alTratarDeInterpretarUnComandoENTRENADORES_VICTORIAS_devuelveElStringCorrecto(){

    salon_t* salon = salon_leer_archivo("src/archivos_prueba/salon_3e.txt");

    if(!salon)
        return;

    char* devuelto1 = salon_ejecutar_comando(salon,"ENTRENADORES:victorias,2");

    pa2m_afirmar(devuelto1 != NULL,"Al tratar de ejecutar el comando ENTRENADORES:VICTORIAS, se ejecuta");
    pa2m_afirmar(strcmp(devuelto1,"Azul\nYony\n") == 0,"La string devuelta es correcta");

    if(devuelto1)
        free(devuelto1);

    char* devuelto2 = salon_ejecutar_comando(salon,"ENTRENADORES:victorias");

    pa2m_afirmar(devuelto2 == NULL,"Al tratar de ejecutar el comando ENTRENADORES:VICTORIAS sin numero de victorias, no se ejecuta");

    if(devuelto2)
        free(devuelto2);

    salon_destruir(salon);

}

void alTratarDeInterpretarUnComandoENTRENADORES_POKEMON_devuelveElStringCorrecto(){

    salon_t* salon = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt");

    if(!salon)
        return;

    char* devuelto1 = salon_ejecutar_comando(salon,"ENTRENADORES:pokemon,pokemon1");

    pa2m_afirmar(devuelto1 != NULL,"Al tratar de ejecutar el comando ENTRENADORES:POKEMON, se ejecuta");
    pa2m_afirmar(strcmp(devuelto1,"entrenador1\n") == 0,"La string devuelta es correcta");
    if(devuelto1)
        free(devuelto1);

    char* devuelto2 = salon_ejecutar_comando(salon,"ENTRENADORES:pokemon,pokemon2");

    pa2m_afirmar(devuelto2 != NULL,"Al tratar de ejecutar el comando ENTRENADORES:POKEMON, se ejecuta por segunda vez");
    pa2m_afirmar(strcmp(devuelto2,"entrenador1\nentrenador2\n") == 0,"La string devuelta es correcta");

    if(devuelto2)
        free(devuelto2);

    salon_destruir(salon);

}


void alTratarDeInterpretarUnComandoEquipo_devuelveElStringCorrecto(){

    salon_t* salon1 = NULL;

    salon1 = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt");

    if(!salon1)
        return;

    char* devuelto1 = salon_ejecutar_comando(salon1,"EQUIPO:entrenador1");

    pa2m_afirmar(devuelto1 != NULL,"Al tratar de ejecutar el comando EQUIPO, se ejecuta");
    pa2m_afirmar(strcmp(devuelto1,"pokemon1,1,2,3,4,5\npokemon2,5,4,3,2,1\n") == 0,"La string devuelta es correcta");

    if(devuelto1)
        free(devuelto1);

    salon_destruir(salon1);

    salon_t* salon2 = salon_leer_archivo("salones/salon_estandar.txt");

    if(!salon2)
        return;

    char* devuelto2 = salon_ejecutar_comando(salon2,"EQUIPO:Lucas");

    pa2m_afirmar(devuelto2 != NULL,"Al tratar de ejecutar el comando EQUIPO por segunda vez, se ejecuta");
    pa2m_afirmar(strcmp(devuelto2,"Pikachu,80,12,43,14,15\nDitto,25,4,3,62,31\nEevee,64,73,33,21,19\nZapdos,35,26,6,52,57\nNidoking,42,56,52,1,16\nScyther,62,16,12,61,12\n") == 0,"La string devuelta es correcta");
    if(devuelto2)
        free(devuelto2);

    char* devuelto3 = salon_ejecutar_comando(salon2,"EQUIPO");

    pa2m_afirmar(devuelto3 == NULL,"Al tratar de ejecutar el comando EQUIPO sin ar+argumentos, no se ejecuta");
    if(devuelto3)
        free(devuelto3);


    salon_destruir(salon2);
}

void alPedirleLasReglasDeCombate_devuelveElStringCorrecto(){

    salon_t* salon = NULL;

    salon = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt");

    if(!salon)
        return;

    char* devuelto = salon_ejecutar_comando(salon,"REGLAS");

    pa2m_afirmar(devuelto != NULL,"Al tratar de ejecutar el comando REGLAS, se ejecuta");
    pa2m_afirmar(strcmp(devuelto,"AGUANTE,3 * defensa + 0.4 * nivel + 2 ∗ fuerza\nCARRERA_DE_OBSTACULOS,2.5 * velocidad + 0.7 * nivel + fuerza\nCLASICO,0.8 ∗ nivel + fuerza + 2 ∗ velocidad\nROMPECABEZAS,4 * inteligencia + 0.3 * nivel + 2 ∗ velocidad\nMODERNO,0.5 ∗ nivel + 0.9 ∗ defensa + 3 ∗ inteligencia\n") == 0,"La string devuelta es correcta");

    if(devuelto)
        free(devuelto);

    salon_destruir(salon);
}

void alPedirleQueCompareDosEntrenadores_devuelveElStringCorrecto(){
    salon_t* salon = NULL;

    salon = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt");

    if(!salon)
        return;

    char* devuelto1 = salon_ejecutar_comando(salon,"COMPARAR:entrenador1,entrenador2,JSANNW");

    pa2m_afirmar(devuelto1 == NULL,"Al tratar de ejecutar el comando COMPARAR con una regla invalida, devuelve un string nulo");

    if(devuelto1)
        free(devuelto1);

    char* devuelto2 = salon_ejecutar_comando(salon,"COMPARAR:entrenador1,entrenador2,CLASICO");

    pa2m_afirmar(devuelto2 != NULL,"Al ejecutar ell compando COMPARAR con reglas y entrenadores validos, se ejecuta");

    pa2m_afirmar(strcmp(devuelto2,"1\n2\n2\n") == 0,"El string devuelto es correcto");

    if(devuelto2)
        free(devuelto2);

    char* devuelto3 = salon_ejecutar_comando(salon,"COMPARAR:entrenador1,entrenador2,MODERNO,12");

    pa2m_afirmar(devuelto3 == NULL,"Al tratar de ejecutar el comando COMPARAR con mas/menos argumentos de los que corresponde, devuelve un string nulo");

    if(devuelto3)
        free(devuelto3);

    salon_destruir(salon);   
}

void alAgregarUnPokemonPorComando_loAgregaYDevuelveElStringCorrecto(){
    salon_t* salon = NULL;

    salon = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt");

    if(!salon)
        return;

    char* devuelto1 = salon_ejecutar_comando(salon,"AGREGAR_POKEMON:asjsa,Abra,1,2,3,4,5");

    pa2m_afirmar(devuelto1 == NULL,"Al tratar de ejecutar el comando AGREGAR_POKEMON con un entrenador que no esat en el salon, devuelve un string nulo");

    if(devuelto1)
        free(devuelto1);

    char* devuelto2 = salon_ejecutar_comando(salon,"AGREGAR_POKEMON:entrenador1,Abra,1,2,3,4,5");

    pa2m_afirmar(devuelto2 != NULL,"Al ejecutar el compando AGREGAR_POKEMON con argumentos validos se ejecuta");

    pa2m_afirmar(strcmp(devuelto2,"OK") == 0,"El string devuelto es correcto");

    if(devuelto2)
        free(devuelto2);

    char* devuelto3 = salon_ejecutar_comando(salon,"EQUIPO:entrenador1");

    pa2m_afirmar(strcmp(devuelto3,"pokemon1,1,2,3,4,5\npokemon2,5,4,3,2,1\nAbra,1,2,3,4,5\n") == 0,"El pokemon se agrega correctamente");

    if(devuelto3)
        free(devuelto3);

    char* devuelto4 = salon_ejecutar_comando(salon,"AGREGAR_POKEMON:entrenador1,Pikachu,1,12");

    pa2m_afirmar(devuelto4 == NULL,"Al tratar de ejecutar el comando AGREGAR_POKEMON con mas/menos argumentos de los que corresponde, devuelve un string nulo");

    if(devuelto4)
        free(devuelto4);

    salon_destruir(salon);   

}

void alQuitarUnPokemonPorComando_loQuitaYDevuelveElStringCorrecto(){
    salon_t* salon1 = NULL;

    salon1 = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt");

    if(!salon1)
        return;

    char* devuelto1 = salon_ejecutar_comando(salon1,"QUITAR_POKEMON:asjsa,Abra");

    pa2m_afirmar(devuelto1 == NULL,"Al tratar de ejecutar el comando QUITAR_POKEMON con un entrenador que no esat en el salon, devuelve un string nulo");

    if(devuelto1)
        free(devuelto1);

    char* devuelto2 = salon_ejecutar_comando(salon1,"QUITAR_POKEMON:entrenador1,Abra");

    pa2m_afirmar(devuelto2 == NULL,"Al ejecutar el compando QUITAR_POKEMON con un pokemon que no tiene el entrenador devuelve un string nulo");

    if(devuelto2)
        free(devuelto2);

    char* devuelto3 = salon_ejecutar_comando(salon1,"QUITAR_POKEMON:entrenador1,pokemon1");

    pa2m_afirmar(strcmp(devuelto3 , "OK") == 0,"Al ejecutar el compando QUITAR_POKEMON con un pokemon que tiene un entrenador se ejecuta");

    if(devuelto3)
        free(devuelto3);

    char* devuelto4 = salon_ejecutar_comando(salon1,"EQUIPO:entrenador1");

    pa2m_afirmar(strcmp(devuelto4,"pokemon2,5,4,3,2,1\n") == 0,"El pokemon se quita correctamente");

    if(devuelto4)
        free(devuelto4);

    char* devuelto5 = salon_ejecutar_comando(salon1,"QUITAR_POKEMON:entrenador1,pokemon2");

    pa2m_afirmar(devuelto5 == NULL,"Al ejecutar el compando QUITAR_POKEMON con un entrenadpr que tiene solo un pokemon no se ejecuta"); 

    if(devuelto5)
        free(devuelto5);

    char* devuelto6 = salon_ejecutar_comando(salon1,"QUITAR_POKEMON:entrenador1,Pikachu,1,12");

    pa2m_afirmar(devuelto6 == NULL,"Al tratar de ejecutar el comando QUITAR_POKEMON con mas/menos argumentos de los que corresponde, devuelve un string nulo");

    if(devuelto6)
        free(devuelto6);

    salon_destruir(salon1);

    salon_t* salon2 = salon_leer_archivo("salones/salon_estandar.txt");

    if(!salon2)
        return;

    char* devuelto7 = salon_ejecutar_comando(salon2,"QUITAR_POKEMON:Mariano,Dragonair");

    pa2m_afirmar(strcmp(devuelto7 , "OK") == 0,"Al tratar de ejecutar el comando QUITAR_POKEMON con un entrenador que esta en el entrenador, devuelve un string OK");

    if(devuelto7)
        free(devuelto7);

    char* devuelto8 = salon_ejecutar_comando(salon2,"EQUIPO:Mariano");

    pa2m_afirmar(strcmp(devuelto8,"Lapras,46,47,18,29,40\nArticuno,21,12,60,14,15\nLapras,81,22,90,7,35\n") == 0,"El pokemon se quita correctamente del eqiipo");

    if(devuelto8)
        free(devuelto8);

    salon_destruir(salon2);
}

void alGuardarUnSalonPorComando_seGuardaYDevuelveElStringCorrecto(){
    salon_t* salon = NULL;

    salon = salon_leer_archivo("src/archivos_prueba/salon_2e_2p.txt");

    if(!salon)
        return;

    char* devuelto1 = salon_ejecutar_comando(salon,"GUARDAR:pruebacomandos.txt");

    pa2m_afirmar(devuelto1 != NULL,"Al ejecutar el compando GUARDAR con un nombre de archivo valido se ejecuta");
    pa2m_afirmar(strcmp(devuelto1,"OK") == 0,"La string es OK");

    if(devuelto1)
        free(devuelto1);

    char* devuelto2 = salon_ejecutar_comando(salon,"GUARDAR");

    pa2m_afirmar(devuelto2 == NULL,"Al ejecutar el compando GUARDAR sin argumentos devuelve un string nulo");

    if(devuelto2)
        free(devuelto2);

    salon_destruir(salon);   
}

int main(){
    pa2m_nuevo_grupo("PRUEBAS DE ENTRENADOR");
    pa2m_nuevo_grupo("Pruebas de crear");
    alCrearUnEntrenador_seCrea();
    alCrearUnPokemon_seCrea();

    pa2m_nuevo_grupo("Pruebas de agregar, obtener y quitar");
    alAgregarUnPokemonAUnEntrenadorNuloOViceversa_noSeAgrega();

    pa2m_nuevo_grupo("PRUEBAS DE SALON");
    pa2m_nuevo_grupo("Pruebas de leer y guardar salon");
    alLeerUnSalonNulo_noSeLee();
    alLeerUnSalonConUnEntrenadorYUnPokemon_SeLee();
    alLeerUnSalonConTresEntrenadoresSinPokemon_SeLee();
    alLeerUnSalonConDosEntrenadoresYDosPokemones_SeLee();

    pa2m_nuevo_grupo("Pruebas de agregar entrenador a salon");
    alAgregarUnEntrenadorAUnSalon_SeAgregaCorrectamente();

    pa2m_nuevo_grupo("Pruebas de filtrar entrenadores");
    alFiltrarEntrenadoresPorSusVictorias_seFiltranCorrectamente();

    pa2m_nuevo_grupo("Pruebas de comandos");
    alTratarDeInterpretarUnComandoInvalido_devuelveNull();
    alTratarDeInterpretarUnComandoENTRENADORES_devuelveElStringCorrecto();
    alTratarDeInterpretarUnComandoENTRENADORES_VICTORIAS_devuelveElStringCorrecto();
    alTratarDeInterpretarUnComandoENTRENADORES_POKEMON_devuelveElStringCorrecto();
    alTratarDeInterpretarUnComandoEquipo_devuelveElStringCorrecto();
    alPedirleLasReglasDeCombate_devuelveElStringCorrecto();
    alPedirleQueCompareDosEntrenadores_devuelveElStringCorrecto();
    alAgregarUnPokemonPorComando_loAgregaYDevuelveElStringCorrecto();
    alQuitarUnPokemonPorComando_loQuitaYDevuelveElStringCorrecto();
    alGuardarUnSalonPorComando_seGuardaYDevuelveElStringCorrecto();
    return pa2m_mostrar_reporte();
}
