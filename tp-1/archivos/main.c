#include "salon.h"
#include "util.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(){

    size_t i;

    printf("Crear un salon usando el archivo 'salon_original.sal'\n");
    salon_t* salon = salon_leer_archivo("salon_original.sal");
    if (!salon){
        salon_destruir(salon);
        return -1;
    }

    printf("\nObtener los entrenadores con al menos 3 ligas ganadas y mostrarlos por pantalla.\n");

    entrenador_t** entrenadores_con_3_o_mas_ganadas = salon_obtener_entrenadores_mas_ganadores(salon, 3);
    size_t cantidad_entrenadores_con_3_o_mas_ganadas = vtrlen(entrenadores_con_3_o_mas_ganadas);
    for(i = 0; i < cantidad_entrenadores_con_3_o_mas_ganadas;i++){
        salon_mostrar_entrenador(entrenadores_con_3_o_mas_ganadas[i]);
    }
    free(entrenadores_con_3_o_mas_ganadas);
   
    printf("\nAgregar 2 entrenadores al salon con 5 y 7 victorias respectivamente.\n");

    entrenador_t* entrenador1 = malloc(sizeof(entrenador_t));
    memset(entrenador1, 0, sizeof(entrenador_t));
    strcpy(entrenador1->nombre, "Juan");
    entrenador1->victorias = 5;
    entrenador1->equipo = NULL;
    entrenador_t* entrenador2 = malloc(sizeof(entrenador_t));
    memset(entrenador2, 0, sizeof(entrenador_t));
    strcpy(entrenador2->nombre, "Maria");
    entrenador2->victorias = 7;
    entrenador2->equipo = NULL;
    salon_agregar_entrenador(salon,entrenador1);
    salon_agregar_entrenador(salon,entrenador2);

    printf("\nObtener los entrenadores con al menos 5 ligas ganadas y mostrarlos por pantalla.\n");
    
    entrenador_t** entrenadores_con_5_o_mas_ganadas = salon_obtener_entrenadores_mas_ganadores(salon, 5);
    size_t cantidad_entrenadores_con_5_o_mas_ganadas = vtrlen(entrenadores_con_5_o_mas_ganadas);
    for(i = 0; i < cantidad_entrenadores_con_5_o_mas_ganadas;i++){
        salon_mostrar_entrenador(entrenadores_con_5_o_mas_ganadas[i]);
    }
    free(entrenadores_con_5_o_mas_ganadas);

    printf("\nGuardar el salon a un nuevo archivo 'salon_modificado.sal'\n");
    
    salon_guardar_archivo(salon, "salon_modificado.sal");

    salon_destruir(salon);

    printf("\nSalir con valor de retorno 0\n");
    return 0;
}
