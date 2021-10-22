#include "lista.h"
#include "pa2mm.h"
#include <stdbool.h>


void alCrearUnaLista_seDevulelveUnaListaValidaConCeroElementos(){

	lista_t* lista = lista_crear();

	pa2m_afirmar(lista != NULL, "El puntero  a lista devuelto es diferente a NULL");
	pa2m_afirmar(lista->cantidad == 0, "La lista tiene 0 elementos");

	lista_destruir(lista);

}

void dadoUnPunteroNulo_alTratarDeInsertarloAUnaLista_seInserta(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar = NULL;

	lista_insertar(lista,elemento_a_agregar);

	pa2m_afirmar(lista->cantidad == 1 && lista->nodo_inicio->elemento == NULL && lista->nodo_fin->elemento == NULL, "Se inserta un elemento NULL");

	lista_destruir(lista);

}

void dadaUnaLista_alAgregarUnElemento_seAgregaCorrectamente(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	int numero_devuelto_1 = lista_insertar(lista,elemento_a_agregar_1);

	pa2m_afirmar(numero_devuelto_1 == 0 && lista->cantidad == 1 && lista->nodo_inicio->elemento == elemento_a_agregar_1 && lista->nodo_fin->elemento == elemento_a_agregar_1, "Se inserta un elemento int en la ultima posicion");

	void* elemento_a_agregar_2 = malloc(sizeof(char));

	int numero_devuelto_2 = lista_insertar(lista,elemento_a_agregar_2);

	pa2m_afirmar(numero_devuelto_2 == 0 && lista->cantidad == 2 && lista->nodo_inicio != lista->nodo_fin && lista->nodo_fin != NULL && lista->nodo_fin->elemento == elemento_a_agregar_2, "Se insertan un elemento int y luego un char");
	
	void* elemento_a_agregar_3 = malloc(sizeof(char));

	int numero_devuelto_3 = lista_insertar(lista,elemento_a_agregar_3);

	void* elemento_a_agregar_4 = malloc(sizeof(char));

	int numero_devuelto_4 = lista_insertar(lista,elemento_a_agregar_4);

	pa2m_afirmar(numero_devuelto_3 == 0 && numero_devuelto_4 == 0 && lista->cantidad == 4 && lista->nodo_inicio->elemento == elemento_a_agregar_1 && lista->nodo_fin->elemento == elemento_a_agregar_4 && lista->nodo_inicio->siguiente->elemento == elemento_a_agregar_2 && lista->nodo_inicio->siguiente->siguiente->elemento == elemento_a_agregar_3, "Se insertan 4 elementos correctamente al final de la lista");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);

	free(elemento_a_agregar_4);


}

void dadaUnaLista_alInsertarUnElementoEnUnaPosicionNoValida_seAgregaAlFinal(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	int numero_devuelto_1 = lista_insertar_en_posicion(lista,elemento_a_agregar_1,100);

	pa2m_afirmar(lista->cantidad == 1 && lista->nodo_inicio->elemento == elemento_a_agregar_1 && lista->nodo_fin == lista->nodo_inicio && numero_devuelto_1 != -1, "Se inserta un elemento al final al darle a la funcion una posicion no valida");

	void* elemento_a_agregar_2 = malloc(sizeof(bool));

	int numero_devuelto_2 = lista_insertar_en_posicion(lista,elemento_a_agregar_2,100);

	pa2m_afirmar(lista->cantidad == 2 && lista->nodo_inicio->elemento == elemento_a_agregar_1 && lista->nodo_fin->elemento == elemento_a_agregar_2 && numero_devuelto_2 != -1, "Se inserta un segundo elemento al final al darle a la funcion una posicion no valida");


	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

}

void dadaUnaLista_alInsertarUnElementoEnUnaPosicionValida_seAgregaCorrectamente(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	int numero_devuelto_1 = lista_insertar_en_posicion(lista,elemento_a_agregar_1,0);

	pa2m_afirmar(lista->cantidad == 1 && lista->nodo_inicio != NULL && lista->nodo_fin == lista->nodo_inicio && numero_devuelto_1 == 0, "Se inserta un elemento al darle a la funcion una lista vacia y una posicion 0");

	void* elemento_a_agregar_2 = malloc(sizeof(int));

	int numero_devuelto_2 = lista_insertar_en_posicion(lista,elemento_a_agregar_2,1);

	pa2m_afirmar(lista->cantidad == 2 && lista->nodo_inicio != NULL && lista->nodo_fin == lista->nodo_inicio->siguiente && numero_devuelto_2 == 0, "Se inserta un elemento al darle a la funcion una lista con un elemento y una posicion 1");

	void* elemento_a_agregar_3 = malloc(sizeof(char));

	int numero_devuelto_3 = lista_insertar_en_posicion(lista,elemento_a_agregar_3,1);

	pa2m_afirmar(lista->cantidad == 3 && lista->nodo_inicio != NULL && lista->nodo_inicio->elemento == elemento_a_agregar_1 && lista->nodo_fin->elemento == elemento_a_agregar_2 && lista->nodo_inicio->siguiente->elemento == elemento_a_agregar_3 && numero_devuelto_3 == 0, "Se inserta un elemento en el medio");

	void* elemento_a_agregar_4 = malloc(sizeof(bool));

	int numero_devuelto_4 = lista_insertar_en_posicion(lista,elemento_a_agregar_4,0);

	pa2m_afirmar(lista->cantidad == 4 && numero_devuelto_4 == 0 && lista->nodo_inicio->elemento == elemento_a_agregar_4 && lista->nodo_inicio->siguiente->elemento == elemento_a_agregar_1 && lista->nodo_inicio->siguiente->siguiente->elemento == elemento_a_agregar_3 && lista->nodo_fin->elemento == elemento_a_agregar_2, "Al darle una posicion de 0, se inserta al inicio de la lista");

	void* elemento_a_agregar_5 = malloc(sizeof(bool));

	int numero_devuelto_5 = lista_insertar_en_posicion(lista,elemento_a_agregar_5,4);

	pa2m_afirmar(lista->cantidad == 5 && numero_devuelto_5 == 0 && lista->nodo_inicio->elemento == elemento_a_agregar_4 && lista->nodo_inicio->siguiente->elemento == elemento_a_agregar_1 && lista->nodo_inicio->siguiente->siguiente->elemento == elemento_a_agregar_3 && lista->nodo_fin->elemento == elemento_a_agregar_5, "Al darle una posicion de 4, se inserta al final de la lista");

	void* elemento_a_agregar_6 = malloc(sizeof(bool));

	int numero_devuelto_6 = lista_insertar_en_posicion(lista,elemento_a_agregar_6,4);

	pa2m_afirmar(lista->cantidad == 6 && numero_devuelto_6 == 0 && lista->nodo_inicio->elemento == elemento_a_agregar_4 && lista->nodo_inicio->siguiente->elemento == elemento_a_agregar_1 && lista->nodo_inicio->siguiente->siguiente->elemento == elemento_a_agregar_3 && lista->nodo_fin->elemento == elemento_a_agregar_5, "Al darle una posicion de 4, se inserta en la anteultima posicicion");


	//Agrege esta prueba dsps de chequear que elemento en posicion funcionara correctamente
	pa2m_afirmar(lista_elemento_en_posicion(lista,4) == elemento_a_agregar_6, "El elemento se inserta en la posicion adecuada");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);

	free(elemento_a_agregar_4);

	free(elemento_a_agregar_5);

	free(elemento_a_agregar_6);
}

void dadaUnaListaVacia_alEliminarElUltimoElemento_noSeEliminaNada(){

	lista_t* lista = lista_crear();

	int numero_devuelto = lista_borrar(lista);

	pa2m_afirmar(numero_devuelto == -1 && lista->cantidad == 0 && lista->nodo_inicio == NULL,"En una lista vacia no se elimina nada");

	lista_destruir(lista);

}

void dadaUnaListaDeDosElementos_alEliminarElUltimoElemento_seEliminaElUltimoElemento(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_1);
	
	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_insertar(lista,elemento_a_agregar_2);

	int numero_devuelto_1 = lista_borrar(lista);

	pa2m_afirmar(numero_devuelto_1 == 0 && lista->cantidad == 1 && lista->nodo_inicio == lista->nodo_fin && lista->nodo_inicio != NULL && lista->nodo_inicio->elemento == elemento_a_agregar_1, "Se elimina el ultimo elemento de una lista de dos elemento, dejando un elemento");

	int numero_devuelto_2 = lista_borrar(lista);

	pa2m_afirmar(numero_devuelto_2 == 0 && lista->cantidad == 0 && lista->nodo_inicio == NULL && lista->nodo_inicio == lista->nodo_fin,"Se elimina el ultimo elemento de una lista, dejando la lista vacia");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);


}

void dadaUnaLista_alEliminarUnaPosicionInvalida_seEliminaElUltimoElemento(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_1);
	
	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_insertar(lista,elemento_a_agregar_2);

	int numero_devuelto_1 = lista_borrar_de_posicion(lista,32);

	pa2m_afirmar(numero_devuelto_1 == 0 && lista->cantidad == 1 && lista->nodo_inicio != NULL && lista->nodo_inicio == lista->nodo_fin && lista->nodo_inicio->elemento == elemento_a_agregar_1, "Al dar una posicion invalida se elimina el ultimo elemento");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

}

void dadaUnaListaYPosicionValidas_alAgregarUnElementoEnUnaPosicionValida_seEliminaElElementoCorrecto(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_1);
	
	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_insertar(lista,elemento_a_agregar_2);

	void* elemento_a_agregar_3 = malloc(sizeof(void*));

	lista_insertar(lista,elemento_a_agregar_3);

	int numero_devuelto_1 = lista_borrar_de_posicion(lista,1);

	pa2m_afirmar(numero_devuelto_1 == 0 && lista->nodo_inicio != NULL && lista->nodo_fin != NULL && lista->nodo_inicio->elemento == elemento_a_agregar_1 && lista->nodo_fin->elemento == elemento_a_agregar_3, "Al dar una posicion valida se elimina el elemento correcto");
	pa2m_afirmar(lista->cantidad == 2,"La lista tiene la cantidad correcta de elementos");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);
	
}

void dadaUnaListaOUnaPosicionNoValida_alAccederAEseElemento_devuelveNull(){

	void* elemento_devuelto_1 = lista_elemento_en_posicion(NULL,0);

	pa2m_afirmar(elemento_devuelto_1 == NULL,"Al acceder a una lista invalida, devuelve NULL");

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_1);
	
	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_insertar(lista,elemento_a_agregar_2);

	void* elemento_a_agregar_3 = malloc(sizeof(void*));

	lista_insertar(lista,elemento_a_agregar_3);

	void* elemento_devuelto_2 = lista_elemento_en_posicion(lista,32);

	pa2m_afirmar(elemento_devuelto_2 == NULL, "Al acceder a una posicion invalida, devuelve NULL");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);

}

void dadaUnaListaYPosicionValidas_alAccederAUnElementoEnUnaPosicionValida_devuelveElElementoCorrecto(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_1);
	
	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_insertar(lista,elemento_a_agregar_2);

	void* elemento_a_agregar_3 = malloc(sizeof(void*));

	lista_insertar(lista,elemento_a_agregar_3);

	void* elemento_devuelto_1 = lista_elemento_en_posicion(lista,0);

	void* elemento_devuelto_2 = lista_elemento_en_posicion(lista,1);

	void* elemento_devuelto_3 = lista_elemento_en_posicion(lista,2);

	pa2m_afirmar(elemento_devuelto_1 == elemento_a_agregar_1, "Al acceder al primer elemento, devuelve el primer elemento");
	pa2m_afirmar(elemento_devuelto_2 == elemento_a_agregar_2, "Al acceder al segundo elemento, devuelve el segundo elemento");
	pa2m_afirmar(elemento_devuelto_3 == elemento_a_agregar_3, "Al acceder al tercer elemento, devuelve el tercer elemento");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);


}

void dadaUnaListaVacia_alAccederAlUltimoElemento_devuelveNull(){

	void* elemento_devuelto_1 = lista_ultimo(NULL);

	lista_t* lista = lista_crear();

	void* elemento_devuelto_2 = lista_ultimo(lista);

	pa2m_afirmar(elemento_devuelto_1 == NULL && elemento_devuelto_1 == elemento_devuelto_2,"En una lista vacia o nula, el ultimo elemento es NULL")

	lista_destruir(lista);

}

void dadaUnaListaNoVacia_alAccederAlUltimoElemento_devuelveEseElemento(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_1);

	void* elemento_devuelto_1 = lista_ultimo(lista);

	pa2m_afirmar(elemento_devuelto_1 == elemento_a_agregar_1, "Al acceder al ultimo elemento de una lista de cantidad 1, devuelve el primer elemento");
	
	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_insertar(lista,elemento_a_agregar_2);

	void* elemento_devuelto_2 = lista_ultimo(lista);

	pa2m_afirmar(elemento_devuelto_2 == elemento_a_agregar_2, "Al acceder al ultimo elemento de una lista de cantidad 2, devuelve el segundo elemento");

	void* elemento_a_agregar_3 = malloc(sizeof(void*));

	lista_insertar(lista,elemento_a_agregar_3);

	void* elemento_devuelto_3 = lista_ultimo(lista);

	pa2m_afirmar(elemento_devuelto_3== elemento_a_agregar_3, "Al acceder al ultimo elemento de una lista de cantidad 3, devuelve el tercer elemento");


	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);

}

void dadaUnaListaVacia_alPregutarSiLaListaEstaVacia_devuelveTrue(){

	bool elemento_devuelto_1 = lista_vacia(NULL);

	lista_t* lista = lista_crear();

	bool elemento_devuelto_2 = lista_vacia(lista);

	pa2m_afirmar(elemento_devuelto_2 == true && elemento_devuelto_1 == elemento_devuelto_2,"Al preguntar si una lista con ningun elemento es nula, devuelve true");

	lista_destruir(lista);

}

void dadaUnaListaNoVacia_alPregutarSiLaListaEstaVacia_devuelveFalse(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_1);

	bool elemento_devuelto = lista_vacia(lista);

	pa2m_afirmar(elemento_devuelto == false,"Al preguntar si una lista con algun elemento es nula, devuelve false");

	lista_destruir(lista);

	free(elemento_a_agregar_1);
}

void dadaUnaListaVacia_alPregutarCuantosElementosTiene_devuelveCero(){

	size_t elemento_devuelto_1 = lista_elementos(NULL);

	lista_t* lista = lista_crear();

	size_t elemento_devuelto_2 = lista_elementos(lista);

	pa2m_afirmar(elemento_devuelto_2 == 0 && elemento_devuelto_1 == elemento_devuelto_2,"Al preguntar cuantos elementos tiene una lista con ningun elemento, devuelve cero");

	lista_destruir(lista);


}

void dadaUnaListaNoVacia_alPregutarCuantosElementosTiene_devuelveLaCantidadDeElementos(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_1);

	size_t elemento_devuelto_1 = lista_elementos(lista);

	pa2m_afirmar(elemento_devuelto_1 == 1, "Una lista de un elemento devuelve que tiene un elemento");

	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_insertar(lista,elemento_a_agregar_2);

	size_t elemento_devuelto_2 = lista_elementos(lista);

	pa2m_afirmar(elemento_devuelto_2 == 2, "Una lista de dos elemento devuelve que tiene un elemento");

	void* elemento_a_agregar_3 = malloc(sizeof(int));

	lista_insertar(lista,elemento_a_agregar_3);

	size_t elemento_devuelto_3 = lista_elementos(lista);

	pa2m_afirmar(elemento_devuelto_3 == 3, "Una lista de tres elemento devuelve que tiene un elemento");


	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);

}

void dadaUnElementoNulo_alTratarDeApilarlo_seApila(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar = NULL;

	int numero_devuelto = lista_apilar(lista,elemento_a_agregar);

	pa2m_afirmar(numero_devuelto == 0 && lista->cantidad == 1 && lista->nodo_inicio->elemento == NULL && lista->nodo_fin->elemento == NULL, "Se apila un elemento NULL");

	lista_destruir(lista);

}

void dadaUnElementoValido_alApilarlo_seApilaCorrectamente(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	int numero_devuelto_1 = lista_apilar(lista,elemento_a_agregar_1);

	pa2m_afirmar(numero_devuelto_1 == 0 && lista->cantidad == 1 && lista->nodo_inicio != NULL && lista->nodo_fin != NULL && lista->nodo_fin->elemento == elemento_a_agregar_1, "Se apila un elemento int en la ultima posicion");

	void* elemento_a_agregar_2 = malloc(sizeof(char));

	int numero_devuelto_2 = lista_apilar(lista,elemento_a_agregar_2);

	pa2m_afirmar(numero_devuelto_2 == 0 && numero_devuelto_2 == numero_devuelto_1 && lista->cantidad == 2 && lista->nodo_inicio != lista->nodo_fin && lista->nodo_fin != NULL && lista->nodo_fin->elemento == elemento_a_agregar_1 && lista->nodo_inicio->elemento == elemento_a_agregar_2, "Se apila un elemento int y luego un char");
	
	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);
}

void dadaUnaListaDeCantidadCero_alTratarDeDesapilar_noSeDesapila(){

	lista_t* lista = lista_crear();

	int numero_devuelto = lista_desapilar(lista);

	pa2m_afirmar(numero_devuelto == -1 && lista->cantidad == 0 && lista->nodo_inicio == NULL && lista->nodo_fin == NULL, "No se desapila un elemento si la lista tiene cantidad cero");

	lista_destruir(lista);

}

void dadaUnaListaDeCantidadDiferenteDeCero_alTratarDeDesapilar_seDesapila(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_apilar(lista,elemento_a_agregar_1);

	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_apilar(lista,elemento_a_agregar_2);

	int numero_devuelto_1 = lista_desapilar(lista);

	pa2m_afirmar(lista->cantidad == 1 && numero_devuelto_1 == 0 && lista->nodo_inicio->elemento == elemento_a_agregar_1,"Se desapila un elemento correctamente");

	int numero_devuelto_2 = lista_desapilar(lista);

	pa2m_afirmar(lista->cantidad == 0 && numero_devuelto_2 == 0 && lista->nodo_inicio== NULL,"Se desapilan dos elementos correctamente");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

}

void dadaUnElementoNulo_alTratarDeEncolarlo_seEncola(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar = NULL;

	int numero_devuelto = lista_encolar(lista,elemento_a_agregar);

	pa2m_afirmar(numero_devuelto == 0 && lista->cantidad == 1 && lista->nodo_inicio->elemento == NULL && lista->nodo_fin->elemento == NULL, "No se encola un elemento NULL");

	lista_destruir(lista);

}

void dadaUnElementoValido_alEncolarlo_seEncolaCorrectamente(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	int numero_devuelto_1 = lista_encolar(lista,elemento_a_agregar_1);

	pa2m_afirmar(numero_devuelto_1 == 0 && lista->cantidad == 1 && lista->nodo_inicio != NULL && lista->nodo_fin != NULL && lista->nodo_fin->elemento == elemento_a_agregar_1, "Se encola un elemento int en la ultima posicion");

	void* elemento_a_agregar_2 = malloc(sizeof(char));

	int numero_devuelto_2 = lista_encolar(lista,elemento_a_agregar_2);

	pa2m_afirmar(numero_devuelto_2 == 0 && lista->cantidad == 2 && lista->nodo_inicio != lista->nodo_fin && lista->nodo_fin != NULL && lista->nodo_fin->elemento == elemento_a_agregar_2, "Se encola un elemento int y luego un char");
	
	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

}

void dadaUnaListaVacia_alDesapilarElUltimoElemento_noSeDesapilaNada(){

	lista_t* lista = lista_crear();	

	int numero_devuelto = lista_desapilar(lista);

	pa2m_afirmar(numero_devuelto == -1,"En una lista vacia no se desapilo nada");

	lista_destruir(lista);

}

void dadaUnaListaNoValida_alAccederAlTope_devuelveNull(){

	lista_t* lista = lista_crear();	

	void* elemento_devuelto = lista_tope(lista);

	pa2m_afirmar(elemento_devuelto == NULL,"En una lista vacia cuando pido el tope devuelve NULL");

	lista_destruir(lista);

}

void dadaUnaLista_alAccederAlTope_devuelveElPrimerElemento(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	lista_apilar(lista,elemento_a_agregar_1);

	void* elemento_devuelto_1 = lista_tope(lista);

	pa2m_afirmar(elemento_devuelto_1 == elemento_a_agregar_1, "Al acceder al tope de una lista de longitud 1, devuelve el primer elemento apilado");
	
	void* elemento_a_agregar_2 = malloc(sizeof(char));

	lista_apilar(lista,elemento_a_agregar_2);

	void* elemento_devuelto_2 = lista_tope(lista);

	pa2m_afirmar(elemento_devuelto_2 == elemento_a_agregar_2, "Al acceder al tope de una lista de longitud 2, devuelve el segundo elemento apilado");

	void* elemento_a_agregar_3 = malloc(sizeof(void*));

	lista_apilar(lista,elemento_a_agregar_3);

	void* elemento_devuelto_3 = lista_tope(lista);

	pa2m_afirmar(elemento_devuelto_3== elemento_a_agregar_3, "Al acceder al tope de una lista de longitud 3, devuelve el tercer elemento apilado");

	void* elemento_a_agregar_4 = malloc(sizeof(bool));

	lista_insertar(lista, elemento_a_agregar_4);

	void* elemento_devuelto_4 = lista_tope(lista);

	pa2m_afirmar(elemento_a_agregar_3 == elemento_devuelto_4, "Al acceder al tope de una lista de longitud 4, devuelve el tercer elemento apilado (el cuarto se inserto al final)");


	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);

	free(elemento_a_agregar_4);
}

void dadaUnaListaVacia_alDesencolarElUltimoElemento_noSeDesencolaNada(){

	lista_t* lista = lista_crear();	

	int numero_devuelto = lista_desencolar(lista);

	pa2m_afirmar(numero_devuelto == -1,"En una lista vacia no se desapilo nada");

	lista_destruir(lista);

}

bool sumarNumeroANodo(void* _elemento,void* _numero){

	int* elemento = _elemento;

	int* numero = _numero;

	if (!elemento)
		return false;

	*(elemento) += *numero;

	return true;
}

void dadaUnaLitsa_alRecorrerLaListaConUnIteradorInternoYSumarleUnoACadaElemento_todosLosElementosSeIncrementanEnUno(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));

	*(int*)elemento_a_agregar_1 = 1;

	lista_insertar(lista,elemento_a_agregar_1);

	void* elemento_a_agregar_2 = malloc(sizeof(int));

	*(int*)elemento_a_agregar_2 = 2;

	lista_insertar(lista,elemento_a_agregar_2);

	void* elemento_a_agregar_3 = malloc(sizeof(int));

	*(int*)elemento_a_agregar_3 = 3;

	lista_insertar(lista,elemento_a_agregar_3);

	int incremento = 1;

	size_t numero_devuelto = lista_con_cada_elemento(lista,sumarNumeroANodo,&incremento);

	pa2m_afirmar(numero_devuelto == 3,"El iterador interno hace 3 iteraciones");
	pa2m_afirmar((*(int*)lista_elemento_en_posicion(lista,0) == 2),"Se incrementa el primer elemento");
	pa2m_afirmar((*(int*)lista_elemento_en_posicion(lista,1) == 3),"Se incrementa el segundo elemento");
	pa2m_afirmar((*(int*)lista_elemento_en_posicion(lista,2) == 4),"Se incrementa el tercer elemento");

	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);

}

void dadaUnaListaNull_alTratarDeCrearUnIterador_devuelveUnIteradorConCorrienteNula(){

	lista_t* lista = lista_crear();

	lista_iterador_t* iterador = lista_iterador_crear(lista);

	pa2m_afirmar(iterador != NULL && iterador->corriente == NULL && iterador->lista == lista,"Al crear un iterador de una lista vacia, se crea un iterador");

	lista_destruir(lista);

	lista_iterador_destruir(iterador);

}
void dadaUnaLista_alTratarDeCrearUnIterador_devuelveUnIterador(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));
	lista_insertar(lista,elemento_a_agregar_1);

	void* elemento_a_agregar_2 = malloc(sizeof(char));
	lista_insertar(lista,elemento_a_agregar_2);

	void* elemento_a_agregar_3 = malloc(sizeof(int));
	lista_insertar(lista,elemento_a_agregar_3);

	lista_iterador_t* iterador = lista_iterador_crear(lista);

	pa2m_afirmar(iterador != NULL,"Al crear un iterador de una lista no vacia, se crea un iterador");
	pa2m_afirmar(iterador->corriente == lista->nodo_inicio, "El iterador se crea con la corriente en la primera posicion de la lista");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

	free(elemento_a_agregar_3);
}

void dadoUnIterador_alVerSiTieneSiguiente_devuelveTrueSiTieneSiguiente(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));
	lista_insertar(lista,elemento_a_agregar_1);

	lista_iterador_t* iterador_1 = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_1), "Un iterador de una lista de un elemento en la primera posicion tiene siguiente");

	lista_iterador_avanzar(iterador_1);
	//Aclaracion: esta prueba se hizo dsps de comprobar que avanzar funciona correctamente

	pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador_1), "Un iterador de una lista de un elemento en la segunda posicion no tiene siguiente");

	pa2m_afirmar(!lista_iterador_tiene_siguiente(NULL),"Un iterador nulo no tiene siguiente")

	lista_iterador_destruir(iterador_1);

	void* elemento_a_agregar_2 = malloc(sizeof(char)*4);
	lista_insertar(lista,elemento_a_agregar_2);

	lista_iterador_t* iterador_2 = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_tiene_siguiente(iterador_2), "Un iterador de una lista de dos elemento, ubicado en el primer elemento tiene siguiente");

	lista_iterador_destruir(iterador_2);
	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

}

void dadoUnIteradorNulo_alTratarDeAvanzar_devuelveFalse(){

	bool valor_devuelto = lista_iterador_avanzar(NULL);

	pa2m_afirmar(!valor_devuelto, "Al tratar de avanzar un iterador nulo, no avanza");

}

void dadoUnIteradorPosicionadoEnElUltimoElemento_alTratarDeAvanzar_devuelveFalse(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));
	lista_insertar(lista,elemento_a_agregar_1);

	lista_iterador_t* iterador_1 = lista_iterador_crear(lista);

	pa2m_afirmar(!lista_iterador_avanzar(iterador_1) && iterador_1->corriente == NULL,"Dado un iterador en la ultima posicion, al avanzar la corriente queda en NULL");

	lista_iterador_destruir(iterador_1);
	lista_destruir(lista);

	free(elemento_a_agregar_1);

}

void dadoUnIteradorNoPosicionadoEnElUltimoElemento_alTratarDeAvanzar_avanzaCorrectamente(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));
	lista_insertar(lista,elemento_a_agregar_1);

	void* elemento_a_agregar_2 = malloc(sizeof(bool));
	lista_insertar(lista,elemento_a_agregar_2);

	lista_iterador_t* iterador = lista_iterador_crear(lista);

	pa2m_afirmar(lista_iterador_avanzar(iterador) && iterador->corriente == lista->nodo_fin,"Dado un iterador no posicionado en la ultima posicion, avanza correctamente");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

}

void dadoUnIteradorNulo_alTratarDeAccederAlElementoActual_devuelveNull(){

	pa2m_afirmar(lista_iterador_elemento_actual(NULL) == NULL, "El elemento actual de un iterador nulo es nulo");

}

void dadoUnIterador_alTratarDeAccederAlElementoActual_devuelveElElementoActual(){

	lista_t* lista = lista_crear();

	void* elemento_a_agregar_1 = malloc(sizeof(int));
	lista_insertar(lista,elemento_a_agregar_1);

	void* elemento_a_agregar_2 = malloc(sizeof(bool));
	lista_insertar(lista,elemento_a_agregar_2);

	lista_iterador_t* iterador = lista_iterador_crear(lista);

	pa2m_afirmar (lista_iterador_elemento_actual(iterador) == lista->nodo_inicio->elemento,"Al acceder al elemento de un iterador en la primera posicion devuelve el primer elemento de la lista");

	lista_iterador_avanzar(iterador);

	pa2m_afirmar (lista_iterador_elemento_actual(iterador) == lista->nodo_fin->elemento,"Al acceder al elemento de un iterador en la segunda posicion devuelve el segundo elemento de la lista");

	lista_iterador_destruir(iterador);
	lista_destruir(lista);

	free(elemento_a_agregar_1);

	free(elemento_a_agregar_2);

}

int main() {
  
  pa2m_nuevo_grupo("Pruebas");
  pa2m_nuevo_grupo("Pruebas de crear lista");
  
  alCrearUnaLista_seDevulelveUnaListaValidaConCeroElementos();
  
  pa2m_nuevo_grupo("Pruebas de Insertar");
  
  dadoUnPunteroNulo_alTratarDeInsertarloAUnaLista_seInserta();
  dadaUnaLista_alAgregarUnElemento_seAgregaCorrectamente();

  pa2m_nuevo_grupo("Pruebas de Insertar por posicion");

  dadaUnaLista_alInsertarUnElementoEnUnaPosicionNoValida_seAgregaAlFinal();
  dadaUnaLista_alInsertarUnElementoEnUnaPosicionValida_seAgregaCorrectamente();

  pa2m_nuevo_grupo("Pruebas eliminar ultimo elemento"); 
  dadaUnaListaVacia_alEliminarElUltimoElemento_noSeEliminaNada();
  dadaUnaListaDeDosElementos_alEliminarElUltimoElemento_seEliminaElUltimoElemento();

  pa2m_nuevo_grupo("Pruebas eliminar cierto elemento");
  dadaUnaLista_alEliminarUnaPosicionInvalida_seEliminaElUltimoElemento();
  dadaUnaListaYPosicionValidas_alAgregarUnElementoEnUnaPosicionValida_seEliminaElElementoCorrecto();

  pa2m_nuevo_grupo("Pruebas acceder a elemento");
  dadaUnaListaOUnaPosicionNoValida_alAccederAEseElemento_devuelveNull();
  dadaUnaListaYPosicionValidas_alAccederAUnElementoEnUnaPosicionValida_devuelveElElementoCorrecto();
  dadaUnaListaVacia_alAccederAlUltimoElemento_devuelveNull();
  dadaUnaListaNoVacia_alAccederAlUltimoElemento_devuelveEseElemento();

  pa2m_nuevo_grupo("Pruebas de lista vacia");
  dadaUnaListaVacia_alPregutarSiLaListaEstaVacia_devuelveTrue();
  dadaUnaListaNoVacia_alPregutarSiLaListaEstaVacia_devuelveFalse();

  pa2m_nuevo_grupo("Pruebas de cantidad de elementos");
  dadaUnaListaVacia_alPregutarCuantosElementosTiene_devuelveCero();
  dadaUnaListaNoVacia_alPregutarCuantosElementosTiene_devuelveLaCantidadDeElementos();

  pa2m_nuevo_grupo("Pruebas de pilas");
  dadaUnElementoNulo_alTratarDeApilarlo_seApila();
  dadaUnElementoValido_alApilarlo_seApilaCorrectamente();
  dadaUnaListaDeCantidadCero_alTratarDeDesapilar_noSeDesapila();
  dadaUnaListaDeCantidadDiferenteDeCero_alTratarDeDesapilar_seDesapila();
  dadaUnaListaVacia_alDesapilarElUltimoElemento_noSeDesapilaNada();
  dadaUnaListaNoValida_alAccederAlTope_devuelveNull();
  dadaUnaLista_alAccederAlTope_devuelveElPrimerElemento();

  pa2m_nuevo_grupo("Pruebas de colas");
  dadaUnElementoNulo_alTratarDeEncolarlo_seEncola();
  dadaUnElementoValido_alEncolarlo_seEncolaCorrectamente();
  dadaUnaListaVacia_alDesencolarElUltimoElemento_noSeDesencolaNada();

  /* Aclaracion: como lista_desencolar y lista_desapilar, lista_tope y
  lista_primero estan implementados completamente igual, hice pruebas
  para cada uno de los dos, ya que como son iguales, si uno funciona bien
  el otro deberia funcionar bien tambien*/

  pa2m_nuevo_grupo("Pruebas de iterador interno");
  dadaUnaLitsa_alRecorrerLaListaConUnIteradorInternoYSumarleUnoACadaElemento_todosLosElementosSeIncrementanEnUno();

  pa2m_nuevo_grupo("Pruebas de iterador externo");
  dadaUnaListaNull_alTratarDeCrearUnIterador_devuelveUnIteradorConCorrienteNula();
  dadaUnaLista_alTratarDeCrearUnIterador_devuelveUnIterador();
  dadoUnIterador_alVerSiTieneSiguiente_devuelveTrueSiTieneSiguiente();
  dadoUnIteradorNulo_alTratarDeAvanzar_devuelveFalse();
  dadoUnIteradorPosicionadoEnElUltimoElemento_alTratarDeAvanzar_devuelveFalse();
  dadoUnIteradorNoPosicionadoEnElUltimoElemento_alTratarDeAvanzar_avanzaCorrectamente();
  dadoUnIteradorNulo_alTratarDeAccederAlElementoActual_devuelveNull();
  dadoUnIterador_alTratarDeAccederAlElementoActual_devuelveElElementoActual();

  return pa2m_mostrar_reporte();
}
