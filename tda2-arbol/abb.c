#include "abb.h"
#include <stdio.h>
#include <stdbool.h>
#define ABB_RECORRER_INORDEN   0
#define ABB_RECORRER_PREORDEN  1
#define ABB_RECORRER_POSTORDEN 2

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

	abb_t* arbol = malloc(sizeof(abb_t));

	if (!arbol)
		return NULL;

	arbol->nodo_raiz = NULL;
	arbol->comparador = comparador;
	arbol->destructor = destructor;


    return arbol;
}

nodo_abb_t* nodo_insertar(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){

	if (!nodo){

		nodo_abb_t* nodo = calloc(1,sizeof(nodo_abb_t));
		if (!nodo){
			free(nodo);
			return NULL;
		}
		nodo->elemento = elemento;
		return nodo;

	}

	int comparacion = comparador(elemento,nodo->elemento);

	if (comparacion > 0)
		nodo->derecha = nodo_insertar(nodo->derecha, elemento, comparador);
	else
		nodo->izquierda = nodo_insertar(nodo->izquierda, elemento, comparador);

	return nodo;
}

int arbol_insertar(abb_t* arbol, void* elemento){

	if (!arbol)
		return -1;

	nodo_abb_t* nodo_insertado = nodo_insertar(arbol->nodo_raiz,elemento,arbol->comparador);

	if (!arbol->nodo_raiz){
		arbol->nodo_raiz = nodo_insertado;
	}

	if (!nodo_insertado)
		return -1;

	return 0;
}


nodo_abb_t* buscar_nodo(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){

	if (!nodo || nodo == NULL)
		return NULL;

	int comparacion = comparador(elemento,nodo->elemento);
	if (comparacion == 0)
		return nodo;
	else{
		if (comparacion > 0)
			return buscar_nodo(nodo->derecha,elemento,comparador);
		else
			return buscar_nodo(nodo->izquierda,elemento,comparador);
	}

}

nodo_abb_t* buscar_nodo_mas_derecho(nodo_abb_t* nodo, nodo_abb_t** extraido){

	if (!nodo)
		return NULL;
	if(nodo->derecha){
		nodo->derecha = buscar_nodo_mas_derecho(nodo->derecha,extraido);
		return nodo;
	}
	*extraido = nodo;
	return nodo->izquierda;


}

nodo_abb_t* nodo_borrar(nodo_abb_t* nodo, void* elemento, abb_liberar_elemento destructor,abb_comparador comparador){

	if (!nodo)
		return NULL;

	int comparacion = comparador(elemento,nodo->elemento);
	if (comparacion == 0 && nodo->elemento == elemento){

		nodo_abb_t* sucesor = NULL;
		nodo->izquierda = buscar_nodo_mas_derecho(nodo->izquierda,&sucesor);

		if (!sucesor){
			nodo_abb_t* nuevo_nodo_para_reemplazar = nodo->derecha;
			if (destructor)
				destructor(nodo->elemento);
			free(nodo);
			return nuevo_nodo_para_reemplazar;
		}

		sucesor->derecha = nodo->derecha;
		sucesor->izquierda = nodo->izquierda;
		if (destructor)
			destructor(nodo->elemento);
		free(nodo);
		return sucesor;

	}
	if (comparacion > 0)
		nodo->derecha = nodo_borrar(nodo->derecha,elemento,destructor,comparador);
	else
		nodo->izquierda = nodo_borrar(nodo->izquierda,elemento,destructor, comparador);

	return nodo;

}

int arbol_borrar(abb_t* arbol, void* elemento){

	if (!arbol)
		return -1;

	nodo_abb_t* nodo_a_borrar = buscar_nodo(arbol->nodo_raiz,elemento,arbol->comparador);
	if (nodo_a_borrar == NULL)
		return -1;
	
	if (arbol->nodo_raiz->elemento == elemento){
		nodo_abb_t* nodo_devuelto = nodo_borrar(arbol->nodo_raiz,elemento,arbol->destructor,arbol->comparador);
		arbol->nodo_raiz = nodo_devuelto;
	}
	else
		nodo_borrar(arbol->nodo_raiz,elemento,arbol->destructor,arbol->comparador);

    return 0;
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	if (!arbol)
		return NULL;
	nodo_abb_t* nodo_encontrado = buscar_nodo(arbol->nodo_raiz,elemento,arbol->comparador);
	if (!nodo_encontrado)
		return NULL;
	void* elemento_a_devolver = nodo_encontrado->elemento;
    return elemento_a_devolver;
}

void* arbol_raiz(abb_t* arbol){
	if (!arbol || !arbol->nodo_raiz)
		return NULL;
    return arbol->nodo_raiz->elemento;
}
bool arbol_vacio(abb_t* arbol){
	if (!arbol || !arbol->nodo_raiz)
		return true;
    return false;
}

void nodo_recorrido_inorden(nodo_abb_t* nodo, void** array, size_t tamanio_array,size_t* contador){

	if (!nodo || *contador >= tamanio_array)
		return;

	if(nodo->izquierda){
		nodo_recorrido_inorden(nodo->izquierda,array,tamanio_array,contador);
	}
	if(nodo && *contador < tamanio_array){
		array[*contador] = nodo->elemento;
		(*contador)++;
	}
	else
		return;
	if (nodo->derecha){
		nodo_recorrido_inorden(nodo->derecha,array,tamanio_array,contador);
	}

	return;
}

size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){

	if (!arbol||!arbol->nodo_raiz||tamanio_array == 0)
		return 0;

	size_t elementos_agregados = 0;
    
    nodo_recorrido_inorden(arbol->nodo_raiz,array,tamanio_array,&elementos_agregados);

    return elementos_agregados;
}

void nodo_recorrido_preorden(nodo_abb_t* nodo, void** array, size_t tamanio_array,size_t* contador){

	if (!nodo || *contador >= tamanio_array)
		return;

	if(nodo && *contador < tamanio_array){
		array[*contador] = nodo->elemento;
		(*contador)++;
	}
	else
		return;
	if(nodo->izquierda){
		nodo_recorrido_preorden(nodo->izquierda,array,tamanio_array,contador);
	}
	if (nodo->derecha){
		nodo_recorrido_preorden(nodo->derecha,array,tamanio_array,contador);
	}

	return;
}

size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){

	if (!arbol||!arbol->nodo_raiz||tamanio_array == 0)
		return 0;

	size_t elementos_agregados = 0;
    
    nodo_recorrido_preorden(arbol->nodo_raiz,array,tamanio_array,&elementos_agregados);

    return elementos_agregados;
}

void nodo_recorrido_postorden(nodo_abb_t* nodo, void** array, size_t tamanio_array,size_t* contador){

	if (!nodo || *contador >= tamanio_array)
		return;

	if(nodo->izquierda){
		nodo_recorrido_postorden(nodo->izquierda,array,tamanio_array,contador);
	}
	if (nodo->derecha){
		nodo_recorrido_postorden(nodo->derecha,array,tamanio_array,contador);
	}
	if(nodo && *contador < tamanio_array){
		array[*contador] = nodo->elemento;
		(*contador)++;
	}
	else
		return;
}

size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){

	if (!arbol||!arbol->nodo_raiz||tamanio_array == 0)
		return 0;

	size_t elementos_agregados = 0;
    
    nodo_recorrido_postorden(arbol->nodo_raiz,array,tamanio_array,&elementos_agregados);

    return elementos_agregados;
}

void destruir_nodo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	//Recorrido postorden para eliminar
	if (nodo->izquierda)
		destruir_nodo(nodo->izquierda,destructor);
	if (nodo->derecha)
		destruir_nodo(nodo->derecha,destructor);
	if (destructor)
		destructor(nodo->elemento);
	free(nodo);

}

void arbol_destruir(abb_t* arbol){

	if (!arbol)
		return;

	if (arbol->nodo_raiz)
		destruir_nodo(arbol->nodo_raiz,arbol->destructor);
	free(arbol);

}

size_t nodo_iterador_inorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, size_t* ptr_contador, bool* seguir_iterando){

	if(!seguir_iterando)
		return *ptr_contador;

	if (!nodo)
		return *ptr_contador;

	if(nodo->izquierda && *seguir_iterando)
		nodo_iterador_inorden(nodo->izquierda,funcion,extra,ptr_contador,seguir_iterando);

	if(*seguir_iterando){
		(*ptr_contador)++;
		if (funcion(nodo->elemento, extra)){
			*seguir_iterando = false; 
			return *ptr_contador;
		}
	}	
	if (nodo->derecha && *seguir_iterando)
		nodo_iterador_inorden(nodo->derecha,funcion,extra,ptr_contador,seguir_iterando);

	return *ptr_contador;

}


size_t nodo_iterador_preorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, size_t* ptr_contador, bool* seguir_iterando){

	if(!seguir_iterando)
		return *ptr_contador;

	if (!nodo)
		return *ptr_contador;

	if(*seguir_iterando){
		(*ptr_contador)++;
		if (funcion(nodo->elemento, extra)){
			*seguir_iterando = false; 
			return *ptr_contador;
		}
	}

	if(nodo->izquierda && *seguir_iterando)
		nodo_iterador_preorden(nodo->izquierda,funcion,extra,ptr_contador,seguir_iterando);

	if (nodo->derecha && *seguir_iterando)
		nodo_iterador_preorden(nodo->derecha,funcion,extra,ptr_contador,seguir_iterando);

	return *ptr_contador;

}

size_t nodo_iterador_postorden(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra, size_t* ptr_contador, bool* seguir_iterando){
	
	if(!(*seguir_iterando))
		return *ptr_contador;

	if (!nodo)
		return *ptr_contador;

	if(nodo->izquierda && *seguir_iterando)
		nodo_iterador_postorden(nodo->izquierda,funcion,extra,ptr_contador,seguir_iterando);

	if (nodo->derecha && *seguir_iterando)
		nodo_iterador_postorden(nodo->derecha,funcion,extra,ptr_contador,seguir_iterando);

	if (*seguir_iterando){
		(*ptr_contador)++;
		if (funcion(nodo->elemento, extra)){
			*seguir_iterando = false; 
			return *ptr_contador;
		}
	}

	return *ptr_contador;

}


size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	
	if (!funcion || !arbol)
    	return 0;

    size_t contador = 0;

    bool seguir_iterando = true;

    if (recorrido == ABB_RECORRER_INORDEN){
    	contador = nodo_iterador_inorden(arbol->nodo_raiz,funcion,extra,&contador,&seguir_iterando);
    	return contador;
    }

    if (recorrido == ABB_RECORRER_PREORDEN){
    	contador = nodo_iterador_preorden(arbol->nodo_raiz,funcion,extra,&contador,&seguir_iterando);
    	return contador;
    }

    if(recorrido == ABB_RECORRER_POSTORDEN){
    	contador = nodo_iterador_postorden(arbol->nodo_raiz,funcion,extra,&contador,&seguir_iterando);
    	return contador;
    }

   	return 0;

}
