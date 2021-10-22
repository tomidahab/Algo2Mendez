TDA LISTA

Una lista es una estructura que puede contener varios elementos adentro de la misma.
La lista tiene varias operaciones, como crear, destruir, insertar, eliminar, vacia, elemento, entre otras.

Hay varios tipos de listas:

Vector estatico: Es como un array comun, las desventajas son que no se puede cambiar el tamaño.

Vector dinamico: Como el que implementamos en el tp anterior, se puede cambiar el tamaño modificando con realloc el bloque al que esta apuntando la lista.

Nodos: El que implementamos en este tda. La ventaja respecto a las otras dos es que no necesita memoria contigua. Son nodos que contienen un elemento y un puntero
a el siguiente nodo, y en algunas implementaciones, al anterior tambien. El ultimo nodo apunta a null, o al primer nodo, depende la implementacion.

A la hora de implementar la lista implemente tambien algunas funciones extra que no estan en el contrato que me ayudaron. Estas son:

    nodo_eliminar_ultimo(nodo_t* nodo):

    Recibe un nodo cualquiera y libera el ultimo nodo de la lista, es decir, el que apunta a NULL, pero no hace nada mas, es decir, el nodo fin de la lista y el nodo
    anterior estan apuntando a un elemento ya liberado, cosa que soluciono en lista_borrar.
    Me sirvio para hacer la funcion lista_borrar que borra el ultimo elemento de la lista.

    elemento_en_posicion(nodo_t* nodo,size_t posicion):

    Recibe un nodo y recursivamente devuelve lo que hay en la posicion que recibe como size_t. Se llama recursivamente cada vez restandose uno en posicion, hasta
    que posicion llega a 0, es ahi cuando devuelve el elemento.
    Me sirvio para hacer lista_elemento_en_posicion recursivamente.

    nodo_destruir_todos(nodo_t* nodo):

    Recibe un nodo, y empezando por ese libera todos los nodos que le siguen.
    Me sirvio para hacer lista_destruir recursivamente.

    nodo_con_cada_elemento(nodo_t* nodo, bool (*funcion)(void*, void*), void *context):

    Me sirvio para implementar lista_con_cada_elemento. Recibe lo mismo que la anterior, excepto que en vez de una lista recibe un nodo. Al llamarla le paso el
    primer nodo.
    Va recorriendo la funcion y hace lo que la funcion le indique recursivamente, mietras no se termine la lista.

Me marie mucho con el tema de iterador externo, pero despues de consultar por slack pude implementar correctamente las pruebas y el codigo.

ACLARACION: A la hora de liberar, pense los elementos de los nodos como punteros a algo en el heap, ya que probablemente al usar una lista en otro contexto,
probablemente se quiera usar en varias funciones separadas una misma lista, y si los elementos estarian almacenados en el stack, desaparecerian.
Implemente las pruebas reservando memoria para comprobar que todo funcione correctamente, y tuve que liberar los elementos en las pruebas.
