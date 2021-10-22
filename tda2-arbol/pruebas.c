#include "abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"
#include <stdbool.h>
#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2
#define PRUEBA_SATISFACTORIA 0
#define CASO_ERROR -1

void eliminar_elemento(void* elemento){

	if (elemento)
		free(elemento);
}

int comparador_enteros(void* _numero1, void* _numero2){
    if(!_numero1 || !_numero2){
        return 0;
    }
	int* numero1 = (int*)_numero1;
	int* numero2 = (int*)_numero2;


	return *numero1 - *numero2;
}

void alCrearUnArbol_alCrearlo_devuelveElArbol(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	pa2m_afirmar(arbol != NULL && arbol->destructor == NULL && arbol->nodo_raiz == NULL && arbol->comparador != NULL,"El arbol se crea correctamente y vacio");

	arbol_destruir(arbol);
}

void dadoUnElemento_alInsertarloEnUnArbol_seInsertaCorrectamente(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	int numero_devuelto_1 = arbol_insertar(arbol, &elemento_1);

	pa2m_afirmar(numero_devuelto_1 == PRUEBA_SATISFACTORIA, "Se inserta un primer elemento"); 
	pa2m_afirmar(arbol->nodo_raiz->elemento == &elemento_1,"Se inserta en la posicion correcta");

	int elemento_2 = 20;

	int numero_devuelto_2 = arbol_insertar(arbol, &elemento_2);

	pa2m_afirmar(numero_devuelto_2 == PRUEBA_SATISFACTORIA, "Se inserta un segundo elemento"); 
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == &elemento_2,"Se inserta en la posicion correcta");

	int elemento_3 = 5;

	int numero_devuelto_3 = arbol_insertar(arbol, &elemento_3);

	pa2m_afirmar(numero_devuelto_3 == PRUEBA_SATISFACTORIA, "Se inserta un tercer elemento"); 
	pa2m_afirmar(arbol->nodo_raiz->izquierda->elemento == &elemento_3,"Se inserta en la posicion correcta");

	int elemento_4 = 15;

	int numero_devuelto_4 = arbol_insertar(arbol, &elemento_4);

	pa2m_afirmar(numero_devuelto_4 == PRUEBA_SATISFACTORIA, "Se inserta un cuarto elemento"); 
	pa2m_afirmar(arbol->nodo_raiz->derecha->izquierda->elemento == &elemento_4,"Se inserta en la posicion correcta");

	int* elemento_5 = malloc(sizeof(int));

	*elemento_5 = 15;

	int numero_devuelto_5 = arbol_insertar(arbol, elemento_5);

	pa2m_afirmar(numero_devuelto_5 == PRUEBA_SATISFACTORIA, "Se inserta un quinto elemento igual al anterior pero que esta en el heap"); 
	pa2m_afirmar(arbol->nodo_raiz->derecha->izquierda->izquierda->elemento == elemento_5,"Se inserta en la posicion correcta");
	
	free(elemento_5);
	arbol_destruir(arbol);
}

void dadoUnElemento_alInsertarloEnUnArbolNulo_noSeInserta(){

	abb_t* arbol = NULL;

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int numero_devuelto_1 = arbol_insertar(arbol, &elemento_1);

	pa2m_afirmar(numero_devuelto_1 == CASO_ERROR, "No se inserta un elemento en un arbol nulo");
}

void dadoUnElementoQueNoEstaEnElArbol_alTratarDeBorrarlo_noLoBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 18;

	int numero_devuelto_1 = arbol_borrar(arbol, &elemento_5);

	pa2m_afirmar(numero_devuelto_1 == CASO_ERROR, "Al tratar de eliminar un elemento que no esta en el arbol no se elimina");

	arbol_destruir(arbol);

	int numero_devuelto_2 = arbol_borrar(NULL,&elemento_5);

	pa2m_afirmar(numero_devuelto_2 == CASO_ERROR, "Al tratar de eliminar un elemento de un arbol NULL no se elimina");
}

void dadoUnElementoQueEstaEnElArbolYNoTieneHijos_siEsRaiz_alTratarDeBorrarloSeBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int numero_devuelto = arbol_borrar(arbol, &elemento_1);

	pa2m_afirmar(numero_devuelto == PRUEBA_SATISFACTORIA, "Al tratar de eliminar un elemento que esta en el nodo raiz y no tiene hijos, se borra");
	pa2m_afirmar(arbol->nodo_raiz == NULL,"El arbol queda vacio");
	arbol_destruir(arbol);	

}

void dadoUnElementoQueEstaEnElArbolYTieneUnHijoALaDerecha_siEsRaiz_alTratarDeBorrarloSeBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int numero_devuelto = arbol_borrar(arbol,&elemento_1);

	pa2m_afirmar(numero_devuelto == PRUEBA_SATISFACTORIA, "Se elimina un elemento que esta en el nodo raiz y tiene un hijo");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento_2,"El nuevo nodo raiz es el unico hijo");

	arbol_destruir(arbol);
}

void dadoUnElementoQueEstaEnElArbolYTieneUnHijoALaIzquierda_siEsRaiz_alTratarDeBorrarloSeBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 5;

	arbol_insertar(arbol, &elemento_2);

	int numero_devuelto = arbol_borrar(arbol,&elemento_1);

	pa2m_afirmar(numero_devuelto == PRUEBA_SATISFACTORIA, "Se elimina un elemento que esta en el nodo raiz y tiene un hijo");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento_2,"El nuevo nodo raiz es el unico hijo");

	arbol_destruir(arbol);
}


void dadoUnElementoQueEstaEnElArbolSinHijos_alTratarDeBorrarlo_seBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int numero_devuelto_1 = arbol_borrar(arbol, &elemento_4);

	pa2m_afirmar(numero_devuelto_1 == PRUEBA_SATISFACTORIA, "Al tratar de borra un elemento sin hijos, se borra");
	pa2m_afirmar(arbol->nodo_raiz->derecha->izquierda == NULL, "El lugar donde estaba queda vacio");

	int numero_devuelto_2 = arbol_borrar(arbol, &elemento_3);

	pa2m_afirmar(numero_devuelto_2 == PRUEBA_SATISFACTORIA, "Al tratar de borra un segundo elemento sin hijos, se borra");
	pa2m_afirmar(arbol->nodo_raiz->izquierda == NULL, "El lugar donde estaba queda vacio");


	arbol_destruir(arbol);

}

void dadoUnElementoQueEstaEnElArbolYTieneDosHijos_siEsRaiz_alTratarDeBorrarloSeBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int numero_devuelto = arbol_borrar(arbol, &elemento_1);

	pa2m_afirmar(numero_devuelto == PRUEBA_SATISFACTORIA, "Al tratar de eliminar un elemento que es raiz y tiene dos hijos se elimina");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == elemento_3 || *(int*)arbol->nodo_raiz->elemento == elemento_2,"Alguno de los dos hijos queda como raiz");
	arbol_destruir(arbol);	

}

void dadoUnElementoQueEstaEnElArbolYTieneUnHijo_siNoEsRaiz_alTratarDeBorrarloSeBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int numero_devuelto = arbol_borrar(arbol, &elemento_2);

	pa2m_afirmar(numero_devuelto == PRUEBA_SATISFACTORIA, "Al tratar de eliminar un elemento que tiene un hijo y no es raiz se elimina");
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == &elemento_4,"El hijo queda en el lugar de ese elemento");
	arbol_destruir(arbol);		

}

void dadoUnElementoQueEstaEnElArbolYTieneDosHijos_siNoEsRaiz_alTratarDeBorrarloSeBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 30;

	arbol_insertar(arbol, &elemento_5);

	int numero_devuelto = arbol_borrar(arbol, &elemento_2);

	pa2m_afirmar(numero_devuelto == PRUEBA_SATISFACTORIA, "Al tratar de eliminar un elemento que tiene dos hijos y no es raiz se elimina");
	pa2m_afirmar(arbol->nodo_raiz->derecha->elemento == &elemento_4 || arbol->nodo_raiz->derecha->elemento == &elemento_5 , "Alguno de los dos hijos queda en su lugar");

	arbol_destruir(arbol);	


}

void dadoUnElementoQueEstaEnElArbolYEstaRepetido_alTratarDeBorrarlo_SeBorra(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 30;

	arbol_insertar(arbol, &elemento_5);

	int elemento_6 = 30;

	arbol_insertar(arbol, &elemento_6);

	int numero_devuelto = arbol_borrar(arbol, &elemento_6);

	pa2m_afirmar(numero_devuelto == PRUEBA_SATISFACTORIA, "Al tratar de eliminar un elemento que esta dos veces en el arbol se elimina");
	pa2m_afirmar(arbol->nodo_raiz->derecha->derecha->elemento == &elemento_5 , "El otro elemento igual permanece en el arbol");


	arbol_destruir(arbol);	

}

void dadoUnElementoQueNoEstaEnElArbol_alTratarDeBuscarlo_devuelveNull(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 19;

	void* elemento_devuelto_1 = arbol_buscar(arbol,&elemento_4);

	pa2m_afirmar(elemento_devuelto_1 == NULL, "Al buscar un elemento que no esta en el arbol devuelve NULL");

	arbol_destruir(arbol);

	void* elemento_devuelto_2 = arbol_buscar(NULL,&elemento_4);

	pa2m_afirmar(elemento_devuelto_2 == NULL, "Al buscar un elemento en un arbol NULL devuelve NULL");

}

void dadoUnElementoQueEstaEnElArbol_alTratarDeBuscarlo_devuelveElElemento(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 5;

	void* elemento_devuelto_1 = arbol_buscar(arbol,&elemento_4);

	pa2m_afirmar(elemento_devuelto_1 == &elemento_3, "Al buscar un elemento que esta en el arbol devuelve ese elemento");

	arbol_destruir(arbol);	

}

void dadoUnArbolNuloOVacio_alBuscarLaRaiz_devuelveNull(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	void* elemento_devuelto_1 = arbol_raiz(arbol);

	pa2m_afirmar(elemento_devuelto_1 == NULL, "Al buscar la raiz de un arbol vacio devuelve NULL");

	arbol_destruir(arbol);	

	void* elemento_devuelto_2 = arbol_raiz(NULL);

	pa2m_afirmar(elemento_devuelto_2 == NULL,"Al buscar la raiz de un arbol NULL devuelve NULL");
}

void dadoUnArbolNoVacio_alBuscarLaRaiz_devuelveLaRaiz(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	void* elemento_devuelto_1 = arbol_raiz(arbol);

	pa2m_afirmar(elemento_devuelto_1 == &elemento_1, "Al buscar la raiz de un arbol no vacio devuelve la raiz");

	arbol_destruir(arbol);	


}

void dadoUnArbolVacioONull_alPreguntarSiEstaVacio_devuelveTrue(){

	bool valor_devuelto_1 = arbol_vacio(NULL);

	pa2m_afirmar(valor_devuelto_1 == true,"Un arbol nulo esta vacio");

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	bool valor_devuelto_2 = arbol_vacio(arbol);

	pa2m_afirmar(valor_devuelto_2 == true,"Un arbol sin nodo raiz esta vacio");

	arbol_destruir(arbol);
}

void dadoUnArbolNoVacio_alPreguntarSiEstaVacio_devuelveFalse(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	bool valor_devuelto_1 = arbol_vacio(arbol);

	pa2m_afirmar(valor_devuelto_1 == false,"Un arbol no nulo no esta vacio");

	arbol_destruir(arbol);	
}

void dadoUnArbolNulo_alPedirleCualquierRecorrido_devuelveCero(){

	void* array[50];

	pa2m_afirmar(arbol_recorrido_inorden(NULL,array,50) == 0,"El recorrido inorden de un arbol null recorre 0");

	pa2m_afirmar(arbol_recorrido_preorden(NULL,array,50) == 0,"El recorrido preorden de un arbol null recorre 0");

	pa2m_afirmar(arbol_recorrido_postorden(NULL,array,50) == 0,"El recorrido postorden de un arbol null recorre 0");

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	pa2m_afirmar(arbol_recorrido_inorden(arbol,array,0) == 0,"El recorrido inorden con un array de tamanio 0 recorre 0");

	pa2m_afirmar(arbol_recorrido_preorden(arbol,array,0) == 0,"El recorrido preorden con un array de tamanio 0 recorre 0");

	pa2m_afirmar(arbol_recorrido_postorden(arbol,array,0) == 0,"El recorrido postorden con un array de tamanio 0 recorre 0");

	arbol_destruir(arbol);
}

void dadoUnArbol_alPedirleElRecorridoInorden_devuelveLaCantidadDeElementosDelArbol(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 30;

	arbol_insertar(arbol, &elemento_5);

	int* array[50];

	pa2m_afirmar(arbol_recorrido_inorden(arbol,(void*)array,50) == 5,"El recorrido inorden de un arbol tamanio 5 recorre 5 elementos");
	pa2m_afirmar(*array[0] == 5,"El primer elemento del array esta bien");
	pa2m_afirmar(*array[1] == 10,"El segundo elemento del array esta bien");
	pa2m_afirmar(*array[2] == 15,"El tercer elemento del array esta bien");
	pa2m_afirmar(*array[3] == 20,"El cuarto elemento del array esta bien");
	pa2m_afirmar(*array[4] == 30,"El quinto elemento del array esta bien");
	arbol_destruir(arbol);

}

void dadoUnArbol_alPedirleElRecorridoPreorden_devuelveLaCantidadDeElementosDelArbol(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 30;

	arbol_insertar(arbol, &elemento_5);

	int* array[50];

	pa2m_afirmar(arbol_recorrido_preorden(arbol,(void*)array,50) == 5,"El recorrido preorden de un arbol tamanio 5 recorre 5 elementos");
	pa2m_afirmar(*array[0] == 10,"El primer elemento del array esta bien");
	pa2m_afirmar(*array[1] == 5,"El segundo elemento del array esta bien");
	pa2m_afirmar(*array[2] == 20,"El tercer elemento del array esta bien");
	pa2m_afirmar(*array[3] == 15,"El cuarto elemento del array esta bien");
	pa2m_afirmar(*array[4] == 30,"El quinto elemento del array esta bien");
	arbol_destruir(arbol);

}

void dadoUnArbol_alPedirleElRecorridoPostorden_devuelveLaCantidadDeElementosDelArbol(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 30;

	arbol_insertar(arbol, &elemento_5);

	int* array[50];

	pa2m_afirmar(arbol_recorrido_postorden(arbol,(void*)array,50) == 5,"El recorrido postorden de un arbol tamanio 5 recorre 5 elementos");
	pa2m_afirmar(*array[0] == 5,"El primer elemento del array esta bien");
	pa2m_afirmar(*array[1] == 15,"El segundo elemento del array esta bien");
	pa2m_afirmar(*array[2] == 30,"El tercer elemento del array esta bien");
	pa2m_afirmar(*array[3] == 20,"El cuarto elemento del array esta bien");
	pa2m_afirmar(*array[4] == 10,"El quinto elemento del array esta bien");
	arbol_destruir(arbol);
}

void dadoUnArbol_alPedirleCualquierRecorridoConUnArrayMasChicoQueSuTamanio_recorreElTamanioDelArray(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 30;

	arbol_insertar(arbol, &elemento_5);

	int* array[3];

	pa2m_afirmar(arbol_recorrido_inorden(arbol,(void*)array,3) == 3,"El recorrido inorden de un arbol con un array menor a su tamanio es del tamanio del array");
	pa2m_afirmar(*array[0] == 5,"El primer elemento del array esta bien");
	pa2m_afirmar(*array[1] == 10,"El segundo elemento del array esta bien");
	pa2m_afirmar(*array[2] == 15,"El tercer elemento del array esta bien");

	pa2m_afirmar(arbol_recorrido_preorden(arbol,(void*)array,3) == 3,"El recorrido preorden de un arbol con un array menor a su tamanio es del tamanio del array");
	pa2m_afirmar(*array[0] == 10,"El primer elemento del array esta bien");
	pa2m_afirmar(*array[1] == 5,"El segundo elemento del array esta bien");
	pa2m_afirmar(*array[2] == 20,"El tercer elemento del array esta bien");

	pa2m_afirmar(arbol_recorrido_postorden(arbol,(void*)array,3) == 3,"El recorrido postorden de un arbol con un array menor a su tamanio es del tamanio del array");
	pa2m_afirmar(*array[0] == 5,"El primer elemento del array esta bien");
	pa2m_afirmar(*array[1] == 15,"El segundo elemento del array esta bien");
	pa2m_afirmar(*array[2] == 30,"El tercer elemento del array esta bien");

	arbol_destruir(arbol);	
}

bool sumarNumeroANodo(void* _elemento,void* _numero){

	int* elemento = _elemento;

	int* numero = _numero;

	if (!elemento)
		return true;

	*elemento += *numero;

	return false;
}

bool encontrarElemento(void* _elemento, void* _elementoActual){

	int* elemento = _elemento;
	int* elementoActual = _elementoActual;

	return *elemento == *elementoActual;
}

void dadoUnIteradorInterno_alRecorrerUnArbolNuloORecorridoNulo_devuelveCero(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	pa2m_afirmar(abb_con_cada_elemento(NULL,ABB_RECORRER_INORDEN,NULL,NULL) == 0,"Al iterar un arbol null, no se itera ningun elemento");

	int numero = 1;

	pa2m_afirmar(abb_con_cada_elemento(arbol,1712761,sumarNumeroANodo,&numero) == 0,"Al iterar un arbol con recorrido no valido, no se itera ningun elemento");

	arbol_destruir(arbol);	
}

void dadoUnIteradorInterno_alRecorrerUnArbolConCualquierRecorrido_devuelveLaCantidadDeElementosEnElArbol(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 30;

	arbol_insertar(arbol, &elemento_5);

	int numero = 1;

	pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,sumarNumeroANodo,&numero) == 5,"Al iterar un arbol con recorrido inorden, se iteran todos los elementos");

	pa2m_afirmar(elemento_1 == 11 && elemento_5 == 31,"La funcion se aplica correctamente");

	pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_PREORDEN,sumarNumeroANodo,&numero) == 5,"Al iterar un arbol con recorrido preorden, se iteran todos los elementos");

	pa2m_afirmar(elemento_1 == 12 && elemento_5 == 32,"La funcion se aplica correctamente");
	
	pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_POSTORDEN,sumarNumeroANodo,&numero) == 5,"Al iterar un arbol con recorrido postorden, se iteran todos los elementos");

	pa2m_afirmar(elemento_1 == 13 && elemento_5 == 33,"La funcion se aplica correctamente");

	arbol_destruir(arbol);

}

void dadoUnIteradorInterno_alRecorrerUnArbolYCuandoLaFuncionDevuelveTrueEnLaMitad_devuelveLaCantidadDeElementosRecorridos(){

	abb_t* arbol = arbol_crear(comparador_enteros, NULL);

	int elemento_1 = 10;

	arbol_insertar(arbol, &elemento_1);

	int elemento_2 = 20;

	arbol_insertar(arbol, &elemento_2);

	int elemento_3 = 5;

	arbol_insertar(arbol, &elemento_3);

	int elemento_4 = 15;

	arbol_insertar(arbol, &elemento_4);

	int elemento_5 = 30;

	arbol_insertar(arbol, &elemento_5);

	int elemento_a_encontrar = 10;

	pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_PREORDEN,encontrarElemento,&elemento_a_encontrar) == 1, "Cuando estas iterando preorden y la funcion devuelve true dejas de iterar");

	pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,encontrarElemento,&elemento_a_encontrar) == 2, "Cuando estas iterando inorden y la funcion devuelve true dejas de iterar");

	pa2m_afirmar(abb_con_cada_elemento(arbol,ABB_RECORRER_POSTORDEN,encontrarElemento,&elemento_a_encontrar) == 5, "Cuando estas iterando postorden y la funcion devuelve true dejas de iterar");

	arbol_destruir(arbol);

}

void dadoUnArbolConDestructor_alEliminarlo_seEliminaCorrectamente(){

	abb_t* arbol = arbol_crear(comparador_enteros, eliminar_elemento);

	void* elemento_1 = malloc(sizeof(int));

	*(int*)elemento_1 = 10;

	arbol_insertar(arbol, elemento_1);

	void* elemento_2 = malloc(sizeof(int));

	*(int*)elemento_2 = 20;

	arbol_insertar(arbol, elemento_2);

	void* elemento_3 = malloc(sizeof(int));

	*(int*)elemento_3 = 5;

	arbol_insertar(arbol, elemento_3);

	void* elemento_4 = malloc(sizeof(int));

	*(int*)elemento_4 = 15;

	arbol_insertar(arbol, elemento_4);

	arbol_destruir(arbol);
}

int main(){

  pa2m_nuevo_grupo("Pruebas de crear arbol");
  alCrearUnArbol_alCrearlo_devuelveElArbol();

  pa2m_nuevo_grupo("Pruebas de insertar");
  dadoUnElemento_alInsertarloEnUnArbolNulo_noSeInserta();
  dadoUnElemento_alInsertarloEnUnArbol_seInsertaCorrectamente();

  pa2m_nuevo_grupo("Pruebas de borrar elemento");
  dadoUnElementoQueNoEstaEnElArbol_alTratarDeBorrarlo_noLoBorra();
  dadoUnElementoQueEstaEnElArbolYNoTieneHijos_siEsRaiz_alTratarDeBorrarloSeBorra();
  dadoUnElementoQueEstaEnElArbolYTieneUnHijoALaDerecha_siEsRaiz_alTratarDeBorrarloSeBorra();
  dadoUnElementoQueEstaEnElArbolYTieneUnHijoALaIzquierda_siEsRaiz_alTratarDeBorrarloSeBorra();
  dadoUnElementoQueEstaEnElArbolYTieneDosHijos_siEsRaiz_alTratarDeBorrarloSeBorra();
  dadoUnElementoQueEstaEnElArbolSinHijos_alTratarDeBorrarlo_seBorra();
  dadoUnElementoQueEstaEnElArbolYTieneUnHijo_siNoEsRaiz_alTratarDeBorrarloSeBorra();
  dadoUnElementoQueEstaEnElArbolYTieneDosHijos_siNoEsRaiz_alTratarDeBorrarloSeBorra();
  dadoUnElementoQueEstaEnElArbolYEstaRepetido_alTratarDeBorrarlo_SeBorra();

  pa2m_nuevo_grupo("Pruebas de buscar");
  dadoUnElementoQueNoEstaEnElArbol_alTratarDeBuscarlo_devuelveNull();
  dadoUnElementoQueEstaEnElArbol_alTratarDeBuscarlo_devuelveElElemento();

  pa2m_nuevo_grupo("Pruebas de raiz");
  dadoUnArbolNuloOVacio_alBuscarLaRaiz_devuelveNull();
  dadoUnArbolNoVacio_alBuscarLaRaiz_devuelveLaRaiz();

  pa2m_nuevo_grupo("Pruebas de vacio");
  dadoUnArbolVacioONull_alPreguntarSiEstaVacio_devuelveTrue();
  dadoUnArbolNoVacio_alPreguntarSiEstaVacio_devuelveFalse();

  pa2m_nuevo_grupo("Pruebas de recorrido");
  dadoUnArbolNulo_alPedirleCualquierRecorrido_devuelveCero();
  dadoUnArbol_alPedirleElRecorridoInorden_devuelveLaCantidadDeElementosDelArbol();
  dadoUnArbol_alPedirleElRecorridoPreorden_devuelveLaCantidadDeElementosDelArbol();
  dadoUnArbol_alPedirleElRecorridoPostorden_devuelveLaCantidadDeElementosDelArbol();
  dadoUnArbol_alPedirleCualquierRecorridoConUnArrayMasChicoQueSuTamanio_recorreElTamanioDelArray();

  pa2m_nuevo_grupo("Pruebas de iterador");
  dadoUnIteradorInterno_alRecorrerUnArbolNuloORecorridoNulo_devuelveCero();
  dadoUnIteradorInterno_alRecorrerUnArbolConCualquierRecorrido_devuelveLaCantidadDeElementosEnElArbol();
  dadoUnIteradorInterno_alRecorrerUnArbolYCuandoLaFuncionDevuelveTrueEnLaMitad_devuelveLaCantidadDeElementosRecorridos();

  //Funcion que chequea si el destructor funciona bien.
  dadoUnArbolConDestructor_alEliminarlo_seEliminaCorrectamente();

  return pa2m_mostrar_reporte();
}
