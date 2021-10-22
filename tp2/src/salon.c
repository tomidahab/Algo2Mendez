#include "salon.h"
#include "hash.h"
#include "lista.h"
#include "util.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIN_ERROR 0
#define ERROR -1
#define FORMATO_ESCRITURA_ENTRENADOR  "%s;%i\n"
#define FORMATO_ESCRITURA_POKEMON     "%s;%i;%i;%i;%i;%i\n"

struct _salon_t{
    lista_t* entrenadores;
    size_t cantidad_entrenadores;
    hash_t* comandos;
    hash_t* reglas;
};

//Clona un string y la reserva en memoria
char* clonar_una_string(const char* s){
  if(!s)
    return NULL;

  char* p = malloc(strlen(s)+1);
  strcpy(p,s);
  return p;
}

//Ejecuta todos los comandos entrenador, y devuelve el string correspondiente o NULL
char* ejecutar_comando_entrenador(salon_t* salon,char* argumentos){
    char** vector_con_argumentos = split(argumentos,',');
    /*if(!tipo)
        return obtener_entrenadores(salon);
    else if(strcmp(tipo,"victorias") == 0)
        return ob*/

    char string[500] = "";
    size_t i;
    entrenador_t* entrenador_actual;
    int victorias_entrenador_actual;
    char victorias_string[256];
    int victorias_minimas = 0;//Me daba error x no inicializar
    char* pokemon_a_tener = NULL; //Me daba error x no inicializar
    if(vtrlen(vector_con_argumentos) != 0){
        if(vtrlen(vector_con_argumentos) != 2){
            vtrfree(vector_con_argumentos);
            return NULL;
        }
        if(strcmp(vector_con_argumentos[0],"victorias") == 0){
            victorias_minimas = atoi(vector_con_argumentos[1]);
        }
        else if(strcmp(vector_con_argumentos[0],"pokemon")){
            pokemon_a_tener = vector_con_argumentos[1];
        }
    }

    for (i = 0; i < lista_elementos(salon->entrenadores); i++){
        entrenador_actual = lista_elemento_en_posicion(salon->entrenadores,i);
        if(vtrlen(vector_con_argumentos) == 0){
            victorias_entrenador_actual = obtener_victorias(entrenador_actual);
            strcat(string,obtener_nombre(entrenador_actual));
            strcat(string,",");
            sprintf(victorias_string,"%i",victorias_entrenador_actual);
            strcat(string,victorias_string);
            strcat(string,"\n");
        }
        else if(strcmp(vector_con_argumentos[0],"victorias") == 0){
            victorias_entrenador_actual = obtener_victorias(entrenador_actual);
            if(victorias_entrenador_actual >= victorias_minimas){
                strcat(string,obtener_nombre(entrenador_actual));
                strcat(string,"\n");
            }
        }
        else{
            pokemon_a_tener = vector_con_argumentos[1];
            if(obtener_pokemon(entrenador_actual,pokemon_a_tener) != NULL){
                strcat(string,obtener_nombre(entrenador_actual));
                strcat(string,"\n");
            }
        }
    }
    vtrfree(vector_con_argumentos);
    char* string_a_devolver = clonar_una_string(string);
    return string_a_devolver;
}

//Corresponde al comando EQUIPO, y devuelve el string correspondiente o NULL
char* devolver_equipo(salon_t* salon,char* argumentos){
    if(!salon || !argumentos)
        return NULL;
    char* string = calloc(1024,sizeof(char));
    if(!string)
        return NULL;
    strcpy(string,"");
    size_t i = 0;
    entrenador_t* entrenador_actual = lista_elemento_en_posicion(salon->entrenadores,i);
    entrenador_t* entrenador_buscado = NULL;
    while(i < salon->cantidad_entrenadores && entrenador_buscado == NULL){
        if(strcmp(argumentos,obtener_nombre(entrenador_actual)) == 0)
            entrenador_buscado = entrenador_actual;
        i++;
        entrenador_actual = lista_elemento_en_posicion(salon->entrenadores,i);
    }
    if(!entrenador_buscado){
        free(string);
        return NULL;
    }

    char nivel_pokemon_actual_string[256];
    char fuerza_pokemon_actual_string[256];
    char inteligencia_pokemon_actual_string[256];
    char velocidad_pokemon_actual_string[256];
    char defensa_pokemon_actual_string[256];
    size_t j = 0;

    pokemon_t* pokemon_actual = obtener_pokemon_con_posicion(entrenador_buscado,j);
    while(pokemon_actual){
        strcat(string,obtener_nombre_pokemon(pokemon_actual));
        strcat(string,",");
        sprintf(nivel_pokemon_actual_string,"%i",obtener_nivel_pokemon(pokemon_actual));
        strcat(string,nivel_pokemon_actual_string);
        strcat(string,",");
        sprintf(defensa_pokemon_actual_string,"%i",obtener_defensa_pokemon(pokemon_actual));
        strcat(string,defensa_pokemon_actual_string);
        strcat(string,",");
        sprintf(fuerza_pokemon_actual_string,"%i",obtener_fuerza_pokemon(pokemon_actual));
        strcat(string,fuerza_pokemon_actual_string);
        strcat(string,",");
        sprintf(inteligencia_pokemon_actual_string,"%i",obtener_inteligencia_pokemon(pokemon_actual));
        strcat(string,inteligencia_pokemon_actual_string);
        strcat(string,",");
        sprintf(velocidad_pokemon_actual_string,"%i",obtener_velocidad_pokemon(pokemon_actual));
        strcat(string,velocidad_pokemon_actual_string);
        strcat(string,"\n");
        j++;
        pokemon_actual = obtener_pokemon_con_posicion(entrenador_buscado,j);
    }
    return string;
}

//Combina dos strings, devuelve true si falla, false si fucniona
bool combinar_strings_hash(hash_t* hash, const char* clave, void* _extra){
    if(!hash || !clave || !_extra)
        return true;

    char* extra = (char*)_extra;
    strcat(extra,clave);
    strcat(extra,",");
    strcat(extra,hash_obtener(hash,clave));
    strcat(extra,"\n");
    return false;
}

// Devuelve las reglas del salon y devuelve el string correspondiente o NULL
char* devolver_reglas(salon_t* salon,char* argumentos){
    if(!salon || argumentos)
        return NULL;
    char* string = calloc(2048, sizeof(char));
    if(!string)
        return NULL;
    strcpy(string,"");
    if(hash_con_cada_clave(salon->reglas,combinar_strings_hash,string) == hash_cantidad(salon->reglas)){
        return string;
    }
    return NULL;
}

//Busca a un entrenador del salon en base a su nombre, y devuelve un punteor a entrenador o NULL
entrenador_t* buscar_entrenador(lista_t* lista_entrenadores,char* nombre_entrenador){
    if(!lista_entrenadores || !nombre_entrenador)
        return NULL;
    size_t i = 0;
    entrenador_t* entrenador_actual;
    while(true){
        entrenador_actual = lista_elemento_en_posicion(lista_entrenadores,i);
        if(!entrenador_actual){
            return NULL;
        }
        i++;
        if(strcmp(obtener_nombre(entrenador_actual),nombre_entrenador) == 0)
            return entrenador_actual;
    }
    return NULL;
}

//Compara dos entrenados en base a las distintas reglas y devuelve el string correspondiente o NULL
char* comparar_entrenadores(salon_t* salon, char* argumentos){
    if(!salon|| !argumentos)
        return NULL;
    char** vector_con_argumentos = split(argumentos,',');
    if(!vector_con_argumentos)
        return NULL;
    if(vtrlen(vector_con_argumentos) != 3){
        vtrfree(vector_con_argumentos);
        return NULL;
    }

    char* string = calloc(1024, sizeof(char));
    if(!string){
        vtrfree(vector_con_argumentos);
        return NULL;
    }

    entrenador_t* entrenador1 = buscar_entrenador(salon->entrenadores, vector_con_argumentos[0]);
    entrenador_t* entrenador2 = buscar_entrenador(salon->entrenadores, vector_con_argumentos[1]);
    if(!entrenador1 || !entrenador2){
        free(string);
        vtrfree(vector_con_argumentos);
        return NULL;
    }
    size_t indice1 = 0;
    size_t indice2 = 0;
    pokemon_t* pokemon_actual_1 = obtener_pokemon_con_posicion(entrenador1,indice1);
    pokemon_t* pokemon_actual_2 = obtener_pokemon_con_posicion(entrenador2,indice2);
    while(pokemon_actual_1 && pokemon_actual_2){
        if(strcmp(vector_con_argumentos[2],"CLASICO") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 8 + 10 * obtener_fuerza_pokemon(pokemon_actual_1) + 20 * obtener_velocidad_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 8 + 10 * obtener_fuerza_pokemon(pokemon_actual_2) + 20 * obtener_velocidad_pokemon(pokemon_actual_2)){
                strcat(string,"1");
                indice2++;
            }
            else{
                indice1++;
                strcat(string,"2");
            }
        }
        else if(strcmp(vector_con_argumentos[2],"MODERNO") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 5 + 9 * obtener_defensa_pokemon(pokemon_actual_1) + 30 * obtener_inteligencia_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 5 + 9 * obtener_defensa_pokemon(pokemon_actual_2) + 30 * obtener_inteligencia_pokemon(pokemon_actual_2)){
                strcat(string,"1");
                indice2++;
            }
            else{
                indice1++;
                strcat(string,"2");
            }
        }
        else if(strcmp(vector_con_argumentos[2],"AGUANTE") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 4 + 30 * obtener_defensa_pokemon(pokemon_actual_1) + 20 * obtener_fuerza_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 4 + 30 * obtener_defensa_pokemon(pokemon_actual_2) + 20 * obtener_fuerza_pokemon(pokemon_actual_2)){
                strcat(string,"1");
                indice2++;
            }
            else{
                indice1++;
                strcat(string,"2");
            }
        }
        else if(strcmp(vector_con_argumentos[2],"ROMPECABEZAS") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 3 + 40 * obtener_inteligencia_pokemon(pokemon_actual_1) + 20 * obtener_velocidad_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 3 + 40 * obtener_inteligencia_pokemon(pokemon_actual_2) + 20 * obtener_velocidad_pokemon(pokemon_actual_2)){
                strcat(string,"1");
                indice2++;
            }
            else{
                indice1++;
                strcat(string,"2");
            }
        }
        else if(strcmp(vector_con_argumentos[2],"CARRERA_DE_OBSTACULOS") == 0){
            if(obtener_nivel_pokemon(pokemon_actual_1) * 7 + 25 * obtener_velocidad_pokemon(pokemon_actual_1) + 10 * obtener_fuerza_pokemon(pokemon_actual_1) >= obtener_nivel_pokemon(pokemon_actual_2) * 7 + 25 * obtener_velocidad_pokemon(pokemon_actual_2) + 10 * obtener_fuerza_pokemon(pokemon_actual_2)){
                strcat(string,"1");
                indice2++;
            }
            else{
                indice1++;
                strcat(string,"2");
            }
        }
        else{
            free(string);
            vtrfree(vector_con_argumentos);
            return NULL;
        }
        pokemon_actual_1 = obtener_pokemon_con_posicion(entrenador1,indice1);
        pokemon_actual_2 = obtener_pokemon_con_posicion(entrenador2,indice2);
        strcat(string,"\n");
    }

    vtrfree(vector_con_argumentos);
    return string;
}

//Agrega un pokemon a un entrenador y devuelve el string "OK" o NULL
char* agregar_pokemon_comando(salon_t* salon,char* argumentos){

    if(!salon|| !argumentos)
        return NULL;
    char** vector_con_argumentos = split(argumentos,',');
    if(!vector_con_argumentos)
        return NULL;
    if(vtrlen(vector_con_argumentos) != 7){
        vtrfree(vector_con_argumentos);
        return NULL;
    }

    char* string = calloc(10, sizeof(char));
    if(!string){
        vtrfree(vector_con_argumentos);
        return NULL;
    }

    entrenador_t* entrenador = buscar_entrenador(salon->entrenadores, vector_con_argumentos[0]);

    if(!entrenador){
        vtrfree(vector_con_argumentos);
        free(string);
        return NULL;
    }

    pokemon_t* pokemon_a_agregar = crear_pokemon(vector_con_argumentos[1],atoi(vector_con_argumentos[2]),atoi(vector_con_argumentos[3]),atoi(vector_con_argumentos[4]),atoi(vector_con_argumentos[5]),atoi(vector_con_argumentos[6]));

    if(!pokemon_a_agregar){
        vtrfree(vector_con_argumentos);
        free(string);
    }
    if(agregar_pokemon(entrenador,pokemon_a_agregar) == ERROR){
        vtrfree(vector_con_argumentos);
        free(string);
        free(pokemon_a_agregar);
        return NULL;
    }
    strcpy(string,"OK");
    vtrfree(vector_con_argumentos);
    return string;
}

//Quita un pokemon de un entrenador y devuelve el string "OK" o NULL
char* quitar_pokemon_comando(salon_t* salon,char* argumentos){
    if(!salon|| !argumentos)
        return NULL;
    char** vector_con_argumentos = split(argumentos,',');
    if(!vector_con_argumentos)
        return NULL;
    if(vtrlen(vector_con_argumentos) != 2){
        vtrfree(vector_con_argumentos);
        return NULL;
    }

    char* string = calloc(10, sizeof(char));
    if(!string){
        vtrfree(vector_con_argumentos);
        return NULL;
    }

    entrenador_t* entrenador = buscar_entrenador(salon->entrenadores, vector_con_argumentos[0]);

    if(!entrenador){
        vtrfree(vector_con_argumentos);
        free(string);
        return NULL;
    }

    pokemon_t* pokemon_a_borrar = obtener_pokemon(entrenador,vector_con_argumentos[1]);

    if(!pokemon_a_borrar){
        vtrfree(vector_con_argumentos);
        free(string);
        return NULL;
    }
    int devuelto = sacar_pokemon(entrenador,pokemon_a_borrar);
    if(devuelto == ERROR){
        vtrfree(vector_con_argumentos);
        free(string);
        return NULL;
    }

    strcpy(string,"OK");
    vtrfree(vector_con_argumentos);
    return string;
}

//Guarda el salon y devuelve el string "OK" si tuvo exito o NULL
char* guardar_salon_comando(salon_t* salon,char* archivo){

    if(!salon || !archivo)
        return NULL;

    if(salon_guardar_archivo(salon,archivo) == ERROR){
        return NULL;
    }
    char* string = calloc(10, sizeof(char));
    strcpy(string,"OK");
    return string;
}

//Crea el hash de comandos para el salon
hash_t* crear_hash_comandos(){
    hash_t* hash = hash_crear(NULL,25);//25 capacidad inicial para que no hayan muchas colisiones y para que nunca tenga que hacer un rehash
    if(!hash)
        return NULL;
    if(hash_insertar(hash,"ENTRENADORES",&ejecutar_comando_entrenador) != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"EQUIPO",&devolver_equipo) != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"REGLAS",&devolver_reglas) != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"COMPARAR",&comparar_entrenadores) != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"AGREGAR_POKEMON",&agregar_pokemon_comando) != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"QUITAR_POKEMON",&quitar_pokemon_comando) != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"GUARDAR",&guardar_salon_comando) != 0){
        hash_destruir(hash);
        return NULL;
    }
    return hash;
}

//Crea el hash de reglas para el salon
hash_t* crear_hash_reglas(){
    hash_t* hash = hash_crear(NULL,25);//25 capacidad inicial para que no hayan muchas colisiones y para que nunca tenga que hacer un rehash
    if(!hash)
        return NULL;
    if(hash_insertar(hash,"CLASICO","0.8 ∗ nivel + fuerza + 2 ∗ velocidad") != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"MODERNO","0.5 ∗ nivel + 0.9 ∗ defensa + 3 ∗ inteligencia") != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"ROMPECABEZAS","4 * inteligencia + 0.3 * nivel + 2 ∗ velocidad") != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"AGUANTE","3 * defensa + 0.4 * nivel + 2 ∗ fuerza") != 0){
        hash_destruir(hash);
        return NULL;
    }
    if(hash_insertar(hash,"CARRERA_DE_OBSTACULOS","2.5 * velocidad + 0.7 * nivel + fuerza") != 0){
        hash_destruir(hash);
        return NULL;
    }
    return hash;
}

//Destruye el salon si existe
void salon_destruir(salon_t* salon){
    if(!salon || !salon->entrenadores)
        return;

    size_t i;
    hash_destruir(salon->comandos);
    hash_destruir(salon->reglas);
    for (i = 0; i < salon->cantidad_entrenadores; i++){
        liberar_entrenador(lista_elemento_en_posicion(salon->entrenadores,i));
    }
    lista_destruir(salon->entrenadores);
    free(salon);
}

//Lee un archivo y lo pasa a un salon reservado en memoria, devuelve un salon_t* si tiene exito y NULL sino
salon_t* salon_leer_archivo(const char* nombre_archivo){
    salon_t* salon = calloc(1,sizeof(salon_t));
    if(!salon)
        return NULL;
    hash_t* hash = crear_hash_comandos();
    if(!hash){
        free(salon);
        return NULL;
    }
    hash_t* hash_reglas = crear_hash_reglas();
    if(!hash){
        free(salon);
        hash_destruir(hash);
        return NULL;
    }
    salon->comandos = hash;
    salon->reglas = hash_reglas;
    FILE* archivo_lectura = fopen(nombre_archivo,"r");
    if (!archivo_lectura){
        free(salon);
        hash_destruir(hash);
        hash_destruir(hash_reglas);
        return NULL;
    }
    salon->entrenadores = lista_crear();
    if(!salon->entrenadores){
        salon_destruir(salon);
        fclosen(archivo_lectura);
        return NULL;
    }
    size_t i;
    entrenador_t* entrenador_actual_en_donde_insertar;
    bool salir_del_loop;
    char* linea = fgets_alloc(archivo_lectura);
    char** vector_a_guardar = split(linea, ';');
    entrenador_t* entrenador_actual = NULL;
    pokemon_t* pokemon_actual = NULL;
    while (vector_a_guardar){
        if (vtrlen(vector_a_guardar) == 2){
            if(buscar_entrenador(salon->entrenadores,vector_a_guardar[0]) != NULL){
                salon_destruir(salon);
                vtrfree(vector_a_guardar);
                fclosen(archivo_lectura);
                free(linea);
                return NULL;
            }
            entrenador_actual = crear_entrenador(vector_a_guardar[0],atoi(vector_a_guardar[1]));
            if (!entrenador_actual){
                salon_destruir(salon);
                vtrfree(vector_a_guardar);
                fclosen(archivo_lectura);
                free(linea);
                return NULL;
            }
        }
        else{
            pokemon_actual = crear_pokemon(vector_a_guardar[0],atoi(vector_a_guardar[1]),atoi(vector_a_guardar[2]),atoi(vector_a_guardar[3]),atoi(vector_a_guardar[4]),atoi(vector_a_guardar[5]));
            if (!pokemon_actual){
                salon_destruir(salon);
                vtrfree(vector_a_guardar);
                fclosen(archivo_lectura);
                free(linea);
                return NULL;
            }
            if(agregar_pokemon(entrenador_actual,pokemon_actual) != SIN_ERROR){
                salon_destruir(salon);
                vtrfree(vector_a_guardar);
                fclosen(archivo_lectura);
                free(linea);
                return NULL;
            }
        }
        free(linea);
        vtrfree(vector_a_guardar);
        linea = fgets_alloc(archivo_lectura);
        vector_a_guardar = split(linea, ';');
        i = 0;
        salir_del_loop = false;
        entrenador_actual_en_donde_insertar = lista_elemento_en_posicion(salon->entrenadores,i);
        if (vtrlen(vector_a_guardar) == 2 || !vector_a_guardar){
            while(entrenador_actual_en_donde_insertar && !salir_del_loop){
                if(strcmp(obtener_nombre(entrenador_actual_en_donde_insertar),obtener_nombre(entrenador_actual)) >= 0){
                    if(lista_insertar_en_posicion(salon->entrenadores, entrenador_actual, i) != SIN_ERROR){
                        salon_destruir(salon);
                        vtrfree(vector_a_guardar);
                        fclosen(archivo_lectura);
                        free(linea);
                        return NULL; 
                    }
                    salir_del_loop = true;
                }
                else{
                    i++;
                    entrenador_actual_en_donde_insertar = lista_elemento_en_posicion(salon->entrenadores,i);
                }

            }
            if(entrenador_actual_en_donde_insertar == NULL){
                if(obtener_pokemon_con_posicion(entrenador_actual,0) == NULL){
                    liberar_entrenador(entrenador_actual);
                    salon_destruir(salon);
                    vtrfree(vector_a_guardar);
                    fclosen(archivo_lectura);
                    free(linea);
                    return NULL; 
                }
                if(lista_insertar(salon->entrenadores, entrenador_actual) != SIN_ERROR){
                    salon_destruir(salon);
                    vtrfree(vector_a_guardar);
                    fclosen(archivo_lectura);
                    free(linea);
                    return NULL; 
                }
            }
            salon->cantidad_entrenadores++;
            entrenador_actual = NULL;
            pokemon_actual = NULL;        
        }
    }  
    free(linea);
    vtrfree(vector_a_guardar);
    fclosen(archivo_lectura);
    return salon;
}    

//Guarda un archuvi de slaon, y devueelve el numero de entrenadores guardados
int salon_guardar_archivo(salon_t* salon, const char* nombre_archivo){
    FILE* archivo_escritura = fopen(nombre_archivo,"w");
    if (!archivo_escritura)
        return ERROR;
    size_t numero_de_entrenadores = salon->cantidad_entrenadores;
    if (numero_de_entrenadores <= 0)
        return ERROR;

    entrenador_t* entrenador_actual;
    size_t numero_de_pokemones;
    size_t i;
    size_t j;
    char* nombre_a_escribir;
    pokemon_t* pokemon_actual;
    for(i = 0; i < numero_de_entrenadores; i++){
        entrenador_actual = lista_elemento_en_posicion(salon->entrenadores,i);
        nombre_a_escribir = obtener_nombre(entrenador_actual);
        fprintf(archivo_escritura,FORMATO_ESCRITURA_ENTRENADOR,nombre_a_escribir,obtener_victorias(entrenador_actual));
        numero_de_pokemones = obtener_numero_pokemones(entrenador_actual);
        for(j = 0; j < numero_de_pokemones;j++){
            pokemon_actual = obtener_pokemon_con_posicion(entrenador_actual,j);
            fprintf(archivo_escritura,FORMATO_ESCRITURA_POKEMON,obtener_nombre_pokemon(pokemon_actual),obtener_nivel_pokemon(pokemon_actual),obtener_defensa_pokemon(pokemon_actual),obtener_fuerza_pokemon(pokemon_actual),obtener_inteligencia_pokemon(pokemon_actual),obtener_velocidad_pokemon(pokemon_actual));
        }      
    }
    fclosen(archivo_escritura);
    return (int)numero_de_entrenadores;
}

//Agrega un entrenador a un salon, devuelve el mismo salon si tiene exito o null sino
salon_t* salon_agregar_entrenador(salon_t* salon, entrenador_t* entrenador){
    if(!salon || !entrenador)
        return NULL;

    size_t i = 0;
    entrenador_t* entrenador_actual_en_donde_insertar = lista_elemento_en_posicion(salon->entrenadores,i);
    while(entrenador_actual_en_donde_insertar){
        if(strcmp(obtener_nombre(entrenador_actual_en_donde_insertar),obtener_nombre(entrenador)) >= 0){
            if(lista_insertar_en_posicion(salon->entrenadores, entrenador, i) != SIN_ERROR){
                return NULL; 
            }
            salon->cantidad_entrenadores++;
            return salon;
        }
        i++;
        entrenador_actual_en_donde_insertar = lista_elemento_en_posicion(salon->entrenadores,i);
    }
    if(lista_insertar(salon->entrenadores, entrenador) != SIN_ERROR){
        return NULL; 
    }
    salon->cantidad_entrenadores++;
    return salon;
}

//Filtra los entrenadores de salon, en base a la funcion que se le pasa, devuelve una lista con los entrenadore sque cumplen las condiciones o null sino
lista_t* salon_filtrar_entrenadores(salon_t* salon , bool (*f)(entrenador_t*, void*), void* extra){
    if(!salon || !f)
        return NULL;

    lista_t* lista_a_devolver = lista_crear();
    if(!lista_a_devolver)
        return NULL;

    size_t i;
    entrenador_t* entrenador_actual;
    for (i = 0; i < salon->cantidad_entrenadores; i++){
        entrenador_actual = lista_elemento_en_posicion(salon->entrenadores,i);
        if (f(entrenador_actual,extra)){
            if(lista_insertar(lista_a_devolver,entrenador_actual) != SIN_ERROR){
                lista_destruir(lista_a_devolver);
                return NULL;
            }
        }
    }
    return lista_a_devolver;
}

//Ejecuta un comando de salon
char* salon_ejecutar_comando(salon_t* salon, const char* comando){
    if (!salon || !comando){
        return NULL;
    }
    char** vector = split(comando,':');
    char* (*funcion)(salon_t*,char*) = hash_obtener(salon->comandos,vector[0]);
    if(!funcion){
        vtrfree(vector);
        return NULL;
    }
    char* string_a_devolver;
    if(vtrlen(vector) >= 2){
        string_a_devolver = funcion(salon,vector[1]);
    }
    else{
        string_a_devolver = funcion(salon,NULL);
    }

    vtrfree(vector);
    return string_a_devolver;
}