#include "hash.h"
#include <stdio.h>
#include "pa2mm.h"
#define ERROR -1
#define SIN_ERROR 0

void destructor(void* elemento){
  return;
}

void dadaUnaCapacidadInicial_alCrearUnHash_seCrea(){

  hash_t* hash_1 = hash_crear(destructor,10);

  pa2m_afirmar(hash_1 != NULL, "El hash se crea correctamente");
  pa2m_afirmar(hash_cantidad(hash_1) == 0, "El hash se crea vacio");

  hash_destruir(hash_1);

  hash_t* hash_2 = hash_crear(destructor,0);

  pa2m_afirmar(hash_2 != NULL, "Al pasarle capacidad maxima 0 el hash se crea correctamente");
  pa2m_afirmar(hash_cantidad(hash_2) == 0, "El hash se crea vacio");

  hash_destruir(hash_2);

  hash_t* hash_3 = hash_crear(NULL,20);

  pa2m_afirmar(hash_3 != NULL, "Al crear un hash sin destructor se crea");
  pa2m_afirmar(hash_cantidad(hash_3) == 0, "El hash se crea vacio");

  hash_destruir(hash_3);
  return;
}

void dadoUnHashNulo_alTratarDeDestruirlo_noSeDestruye(){

  hash_destruir(NULL);//Si no rompe nada es que funciona

}

void dadoUnHashVacio_alTratarDeObtenerAlgo_devuelveNulo(){

  hash_t* hash = hash_crear(destructor,3);

  char* clave = "Eyyy q ondaaa";
  pa2m_afirmar(!hash_obtener(hash,clave), "Al tratar de buscar una clave en un arbol vacio, no la encuentra");
  pa2m_afirmar(!hash_contiene(hash,clave), "El hash no contiene una clave que no le insertamos");


  hash_destruir(hash);
}

void dadoUnHashNoVacio_alTratarDeObtenerAlgo_devuelveElElementoEncontrado(){

  int devuelto;

  hash_t* hash = hash_crear(destructor,3);

  int uno = 1;
  char* clave1 = "Uno";
  devuelto = hash_insertar(hash,clave1,&uno);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(hash_obtener(hash,clave1) == &uno, "Al tratar de buscar un elemento en un arbol de un elemento, la encuentra");
  pa2m_afirmar(hash_contiene(hash,clave1), "El hash contiene una clave que le insertamos");

  int dos = 2;
  char* clave2 = "Dos";
  devuelto = hash_insertar(hash,clave2,&dos);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(hash_obtener(hash,clave1) == &uno, "Al tratar de buscar un elemento en un arbol de dos elemento, encuentra la primera");
  pa2m_afirmar(hash_obtener(hash,clave2) == &dos, "Al tratar de buscar un elemento en un arbol de dos elemento, encuentra la segunda");
  pa2m_afirmar(hash_contiene(hash,clave1), "El hash sigue contieniendo una clave que le insertamos");
  pa2m_afirmar(hash_contiene(hash,clave2), "El hash contiene una clave que le insertamos");

  int tres = 3;
  char* clave3 = "Tres";
  devuelto = hash_insertar(hash,clave3,&tres);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(hash_obtener(hash,clave1) == &uno, "Al tratar de buscar un elemento en un arbol de tres elemento, encuentra la primera");
  pa2m_afirmar(hash_obtener(hash,clave2) == &dos, "Al tratar de buscar un elemento en un arbol de tres elemento, encuentra la segunda");
  pa2m_afirmar(hash_obtener(hash,clave3) == &tres, "Al tratar de buscar un elemento en un arbol de tres elemento, encuentra la tercera");
  pa2m_afirmar(hash_contiene(hash,clave1), "El hash sigue contieniendo la primer clave que le insertamos");
  pa2m_afirmar(hash_contiene(hash,clave2), "El hash sigue contieniendo la segunda clave que le insertamos");
  pa2m_afirmar(hash_contiene(hash,clave3), "El hash contiene una clave que le insertamos");

  int once = 11;
  devuelto = hash_insertar(hash,clave1,&once);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(hash_obtener(hash,clave1) == &once, "Al tratar de buscar un elemento que se sobreescribio, lo encuentra");
  pa2m_afirmar(hash_contiene(hash,clave1), "El hash sigue contieniendo una clave sobreescrita");

  hash_destruir(hash);
}

void dadoUnHashNoLleno_alInsertar_seInsertaCorrectamente(){

  hash_t* hash = hash_crear(destructor,3);
  int devuelto;


  int uno = 1;
  char* clave1 = "Uno";
  devuelto = hash_insertar(hash,clave1,&uno);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(devuelto == SIN_ERROR,"Se inserta sin errores");
  pa2m_afirmar(hash_cantidad(hash) == 1, "Se llena un espacio del hash");
  pa2m_afirmar(hash_obtener(hash,clave1) == &uno, "El elemento insertado esta en el hash");

  int dos = 2;
  char* clave2 = "Dos";
  devuelto = hash_insertar(hash,clave2,&dos);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(devuelto == SIN_ERROR,"Se inserta sin errores");
  pa2m_afirmar(hash_cantidad(hash) == 2, "Se llena otro espacio del hash");
  pa2m_afirmar(hash_obtener(hash,clave2) == &dos, "El elemento insertado esta en el hash");
  pa2m_afirmar(hash_obtener(hash,clave1) == &uno, "No pisa a los valores que estaban antes");

  int tres = 3;
  char* clave3 = "Tres";
  devuelto = hash_insertar(hash,clave3,&tres);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(devuelto == SIN_ERROR,"Se inserta sin errores");
  pa2m_afirmar(hash_cantidad(hash) == 3, "Se llena otro espacio del hash");
  pa2m_afirmar(hash_obtener(hash,clave3) == &tres, "El elemento insertado esta en el hash");
  pa2m_afirmar(hash_obtener(hash,clave1) == &uno, "No pisa al primer valor que estaban antes");
  pa2m_afirmar(hash_obtener(hash,clave2) == &dos, "No pisa al segundo valor que estaban antes");

  int once = 11;
  devuelto = hash_insertar(hash,clave1,&once); //Aca el valor de la clave Uno se deberia sobreescribir
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(devuelto == SIN_ERROR,"Se inserta sin errores");
  pa2m_afirmar(hash_cantidad(hash) == 3, "Se sobreescribe un elemento al hash");
  pa2m_afirmar(hash_obtener(hash,clave1) == &once, "Pisa al valor con la misma clave que estaban antes");
  pa2m_afirmar(hash_obtener(hash,clave2) == &dos, "No pisa al segundo valor que estaban antes");
  pa2m_afirmar(hash_obtener(hash,clave3) == &tres, "No pisa al tercer valor que estaban antes");

  int cientoonce = 111;
  devuelto = hash_insertar(hash,clave1,&cientoonce);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(devuelto == SIN_ERROR,"Se inserta sin errores");
  pa2m_afirmar(hash_cantidad(hash) == 3, "Se sobreescribe otro elemento al hash");
  pa2m_afirmar(hash_obtener(hash,clave1) == &cientoonce, "Pisa al valor con la misma clave que estaban antes");
  pa2m_afirmar(hash_obtener(hash,clave2) == &dos, "No pisa al segundo valor que estaban antes");
  pa2m_afirmar(hash_obtener(hash,clave3) == &tres, "No pisa al tercer valor que estaban antes");


  hash_destruir(hash);

}

void dadoUnHash_alPedirleLaCantidad_devuelveLaCantidadCorrecta(){

  int devuelto;

  hash_t* hash = hash_crear(destructor,3);

  int uno = 1;
  char* clave1 = "Uno";
  devuelto = hash_insertar(hash,clave1,&uno);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }

  pa2m_afirmar(hash_cantidad(hash) == 1,"Devuelve la cantidad correcta con 1 elemento");

  int dos = 2;
  char* clave2 = "Dos";
  devuelto = hash_insertar(hash,clave2,&dos);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }

  pa2m_afirmar(hash_cantidad(hash) == 2,"Devuelve la cantidad correcta con 2 elementos");

  int tres = 3;
  char* clave3 = "Tres";
  devuelto = hash_insertar(hash,clave3,&tres);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }

  pa2m_afirmar(hash_cantidad(hash) == 3,"Devuelve la cantidad correcta con 3 elementos");

  int once = 11;
  devuelto = hash_insertar(hash,clave1,&once);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(hash_cantidad(hash) == 3, "Devuelve la cantidad correcta cuando se sobreescribio un elemento");

  hash_destruir(hash);
}

void dadoUnHashNulo_alTratarDeInsertarAlgo_noSeInserta(){

  int uno = 1;
  char* clave1 = "Uno";
  int devuelto = hash_insertar(NULL,clave1,&uno);
  pa2m_afirmar(devuelto == ERROR,"Al insertar un elemento en un hash nulo, no se inserta");

}

void dadoUnHash_alTratarDeBorrarUnaClaveQueEsta_loElimina(){

  int devuelto;

  hash_t* hash = hash_crear(destructor,3);

  int uno = 1;
  char* clave1 = "Uno";
  devuelto = hash_insertar(hash,clave1,&uno);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }

  pa2m_afirmar(hash_quitar(NULL,clave1) == ERROR,"Al tratar de eliminar en un hash nulo no se elimina");
  pa2m_afirmar(hash_quitar(hash,NULL) == ERROR,"Al tratar de eliminar una clave nula no se elimina");
  pa2m_afirmar(hash_quitar(hash,clave1) == SIN_ERROR,"Al tratar de eliminar una clave en un hash con una clave se elimina");
  pa2m_afirmar(hash_cantidad(hash) == 0, "El hash queda vacio");

  int dos = 2;
  char* clave2 = "Dos";
  devuelto = hash_insertar(hash,clave2,&dos);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }

  int tres = 3;
  char* clave3 = "Tres";
  devuelto = hash_insertar(hash,clave3,&tres);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(hash_quitar(hash,clave2) == SIN_ERROR,"Al tratar de eliminar una clave en un hash con dos claves se elimina");
  pa2m_afirmar(hash_cantidad(hash) == 1, "El hash queda con un elemento");

  int once = 11;
  devuelto = hash_insertar(hash,clave1,&once);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }

  int cientoonce = 111;
  devuelto = hash_insertar(hash,clave1,&cientoonce);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }

  pa2m_afirmar(hash_quitar(hash,clave1) == SIN_ERROR,"Al tratar de eliminar una clave en un hash que se sobreescribio se elimina");
  pa2m_afirmar(hash_cantidad(hash) == 1, "El hash queda con un elemento");
  
  hash_destruir(hash);  

}

bool es_el_elemento_menor_a_diez(hash_t* hash,const char* clave,void* _elemento_2){

  if(!hash || !clave || ! _elemento_2)
    return false;

  int* elemento_1 = (int*)hash_obtener(hash,clave);
  int* elemento_2 = (int*)_elemento_2;
  printf("Es %i mayor a %i? ",*elemento_1,*elemento_2);

  if(*elemento_1 > *elemento_2){
    printf("Si, es mayor asi que termino de iterar\n");
    return true;
  }
  printf("No, sigo iterando a menos que haya llegado al final\n");
  return false;
}

void dadoUnHash_alIterarlo_seIteraCorrectamente(){

  int extra = 10;
  int devuelto;

  pa2m_afirmar(hash_con_cada_clave(NULL,es_el_elemento_menor_a_diez,&extra) == 0, "Al iterar sobre un hash nulo, no se itera ningun elemento");

  hash_t* hash = hash_crear(destructor,3);

  if(!hash){
    printf("Problema de memoria\n");
    exit(-1);
  }
  pa2m_afirmar(hash_con_cada_clave(hash,es_el_elemento_menor_a_diez,&extra) == 0, "Al iterar sobre un hash vacio, no se itera ningun elemento");

  int uno = 1;
  char* clave1 = "Uno";
  devuelto = hash_insertar(hash,clave1,&uno);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }

  pa2m_afirmar(hash_con_cada_clave(hash,NULL,&extra) == 0, "Al iterar sobre un hash con funcion nula, no se itera ningun elemento");
  pa2m_afirmar(hash_con_cada_clave(hash,es_el_elemento_menor_a_diez,&extra) == 1, "Al iterar sobre un hash con un elemento, se itera un elemento");

  int dos = 2;
  char* clave2 = "Dos";
  devuelto = hash_insertar(hash,clave2,&dos);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(hash_con_cada_clave(hash,es_el_elemento_menor_a_diez,&extra) == 2, "Al iterar sobre un hash dos elementos, se iteran dos elemento");

  int tres = 3;
  char* clave3 = "Tres";
  devuelto = hash_insertar(hash,clave3,&tres);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  pa2m_afirmar(hash_con_cada_clave(hash,es_el_elemento_menor_a_diez,&extra) == 3, "Al iterar sobre un hash tres eleementos, se iteran tres elemento");

  int once = 11;
  devuelto = hash_insertar(hash,clave1,&once);
  if(devuelto == ERROR){
    printf("Problema de memoria\n");
    hash_destruir(hash);
    exit(-1);
  }
  size_t devolucion = hash_con_cada_clave(hash,es_el_elemento_menor_a_diez,&extra);
  pa2m_afirmar(3 >= devolucion && devolucion >= 1, "Al iterar sobre un hash con un elemento que va a devolver true, va a iterar correctamente");

  hash_destruir(hash);
}

int main(){

  pa2m_nuevo_grupo("PRUEBAS");

  pa2m_nuevo_grupo("Pruebas de crear y destruir");
  dadaUnaCapacidadInicial_alCrearUnHash_seCrea();
  dadoUnHashNulo_alTratarDeDestruirlo_noSeDestruye();

  pa2m_nuevo_grupo("Pruebas de insertar");
  dadoUnHashNulo_alTratarDeInsertarAlgo_noSeInserta();
  dadoUnHashNoLleno_alInsertar_seInsertaCorrectamente();

  pa2m_nuevo_grupo("Pruebas de obtener y contener");
  dadoUnHashVacio_alTratarDeObtenerAlgo_devuelveNulo();
  dadoUnHashNoVacio_alTratarDeObtenerAlgo_devuelveElElementoEncontrado();

  pa2m_nuevo_grupo("Pruebas de cantidad");
  dadoUnHash_alPedirleLaCantidad_devuelveLaCantidadCorrecta();

  pa2m_nuevo_grupo("Pruebas de borrar");
  dadoUnHash_alTratarDeBorrarUnaClaveQueEsta_loElimina();

  pa2m_nuevo_grupo("Pruebas de iterador");
  dadoUnHash_alIterarlo_seIteraCorrectamente();

  return pa2m_mostrar_reporte();
}
