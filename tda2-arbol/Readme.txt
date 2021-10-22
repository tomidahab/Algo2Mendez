TDA ARBOL

Un arbol es una estructura formada por elementos enlazados. El arbol contiene una raiz, que tiene punteros a 
dos o mas elementos, a los cuales se los llama "Hijos". En caso de no tener hijos, ese puntero estara 
apuntando a NULL. Los arboles son muy recursivos.

Los arboles binarios se caracterizan porque cada nodo tiene dos nodos hijos. Cada nodo tiene un elemento y 
dos punteros, uno que apunta a la derecha y otro que apunta a la izquierda.

Los arboles de busqueda binaria son como los binarios, pero con la caracteriztica de que los nodos que estan 
situados a la izquierda siempre son menores (determinado por un comparador) que cualquier nodo a su derecha,
y los derechos son mayores a los izquierdos. Se eligen en vez de las listas, para que la complejidad de 
busqueda sea O(log n).

Es importante distinguirlos porque dependiendo de que necesitamos hacer, vamos a necesitar un tipo de arbol
diferente.

Para arbol_insertar implemente una funcion llamada nodo_insertar que me permite hacer arbol_insertar
recursivamente. Lo que hace esta funcion es va recorriendo el arbol para un lado o para el otro, segun
el valor que le quiero insertar (usando el comparador para saber si a la izquierda o a la derecha)
hasta que llega a un nodo vacio, que cuando pasa eso, crea un nodo con ese elemento, y le pasa el puntero
a el padre. Recibe un nodo, un puntero a elemento y el comparador del arbol.

Otra funcion que implemente fue buscar_nodo que lo que hace es que yo le paso un elemento, un nodo y un 
comparador y busca un nodo que tenga el mismo elemento que le pase y lo devuelve. Lo hace recursivamente,
recorriendo la funcion hacia la izquierda o hacia la derecha (determinando hacia donde con el comparador).
Esta funcion me sirvio para implementar arbol_borrar y arbol_buscar.

La funcion buscar_nodo_mas_derecho la implemente basicamente para buscar el sucesor (en este caso el
mas derecho de la izquierda, osea el mayor de los menores) que sirve para saber en el caso de que el 
nodo tenga dos hijos, al borrarlo, cual nodo va a tomar su lugar. Lo implemente recursivamente. 
Recibe un nodo, y un extraido, que es donde se va a guardar el nodo cuyo hijo izquierdo se devuelve.

Para la funcion arbol_borrar tuve que implementar un nodo_borrar. Al llamar a arbol_borrar, se fija 
primero si hay arbol, y despues busca si el elemento que quiero borrar esta en el arbol, usando 7
buscar_nodo. Si se cumple que existe el arbol y el elemento que busco esta en el arbol, sigo,
sino devuelvo -1. Despues sigue y llama a nodo_borrar y dependiendo de si estoy borrando un 
nodo_raiz o uno que no es raiz, asigna o no un nuevo nodo_raiz, siempre llamando a nodo_borrar.
La funcion nodo_borrar, recibe un nodo, un elemento y el comparador y destructor del arbol. Esta implementada
de forma recursiva. Primero se fija si el nodo actual es el que quiero borrar, con el comparador, y si no es,
voy a llamar a esta misma funcion con el nodo de la derecha o el de la izquierda segun corresponda. En caso 
de que este sea el nodo que quiero borrar, busco un nuevo nodo que sea el sucesor de este que estoy borrando,
y dependiendo de si ese nodo es nulo o no, voy a reasignar los punteros y borrar el nodo que quiero eliminar.
Fue la funcion que mas problemas me dio.

Despues implemente funciones nodo_recorrido para los 3 recorridos diferentes que me sirven para implementar
los recorridos que pasan los elementos del arbol al array recursivamente, cada uno con un contador que sirve
para saber en que elemento del array tiene que asignar el elemento actual.

Nodo_destruir lo use para destruir el arbol recursivamente, le paso el nodo_raiz y recursivamente hace un
recorrido postorden para eliminar cada nodo.

Despues, implemente un nodo_iterador para cada recorrido, que lo que hace es, recursivamente, recorre la 
funcion segun su recorrido y va aplicando la funcion hasta que devuelve true, y entonces hace un return
con un contador que lleva, de cuantos elementos itero. UPDATE: Tuve que cambiar un par de cosas de esta funcion,
principalmente, agrege un bool que le dice si seguir iterando o no (dependiendo de si la funcion devolvio true)
y en caso de que la funcion haya devuelto true, no lo dejo hacer nada al iterador.