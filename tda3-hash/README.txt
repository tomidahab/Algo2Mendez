A SABER

El hash implementado es cerrado (direccionamiento abierto).

Las coliciones para insertar, se resuelven buscando el siguiente espacio libre.

Lo que se almacenan en el hash son pares, que contienen un una clave, un elemento y un flag para saber si ese espacio ya estuvo ocupado.

La clave que almaceno en el hash es una clave clonada de la que me pasan.

Para cada vez que se inserta un elemento, se reserva memoria para el par, y cuando se quita un elemento, no se libera el elemento, sino
que se deja reservado hasta que haya un rehash o se destruya el hash.

Para buscar, se va fijando desde la posicion que devolvio la funcion de hash, hasta encontrar un espacio nulo que NO haya
sido ocupado todavia o encuentre lo que busca.

_______________________________________________________________________________________________________________________________
TEORIA HASH

Una tabla de hash es basicamente un tipo de dato abstracto el cual contiene valores, los cuales tienen asignados una clave.
Si yo tengo una clave que tengo esta en una tabla de hash, puedo perdile al hash que me de el elemento que tiene asignado esa
clave.
La tabla de hash tiene la ventaja de que para encontrar un elemento, insertarlo y eliminarlo (cuando no hay colisiones) es O(1)
Que es una colision?
Una colision es lo que sucede cuando por ejemplo yo trato de insertar un par clave elemento y al tratar de insertarlo me doy
cuenta que el valor que me devolvio la funcion hash ya esta ocupado. En ese caso lo que hago es ir al elemento proximo mas
cercano que este vacio.
X ejemplo, como lo hice en mi implementacion: Supongamos que tengo una tabla cerrada (direccionamiento abierto) de este tipo:

POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								|---|
0				 		CERO					|281|
												|---|
1		   		 		---     				|   |			 
												|---|
2		   				---						|   |
												|---|
3				 		UNO					    |172|	
												|---|
4						---						|   |
												|---|

Ahora trato de agregar un par clave valor DOS, 918 y la funcion de hash devuelve el valor 0.

POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								|---|
0				 		CERO					|281|<------- DOS     918
												|---|
1		   		 		---     				|   |			 
												|---|
2		   				---						|   |
												|---|
3				 		UNO					    |172|	
												|---|
4						---						|   |
												|---|

Pero no puedo insertarlo, porque esta ocupada esa posicion, entonces lo que pasa se llama colision.

En mi implementacion, ese par nuevo que quiero insertar se moveria al proximo espacio libre de esta manera:

POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								|---|
0				 		CERO					|281|
												|---|
1		   		 		DOS     				|918|			 
												|---|
2		   				---						|   |
												|---|
3				 		UNO					    |172|	
												|---|
4						---						|   |
												|---|

Y asi se resolveria la colision.

REHASH

El rehash es lo que hay que hacer cuando los elementos que contienen llegan a tan punto que estas teniendo demasiadas
colisiones, por lo cual lo que se hace es aumentar el tamanio de la tabla de hash para bajar el numero de colisiones
que estamos teniendo, asi disminuimos la complejidad algoritmica.

Hay dos tipos de hash que vimos en clase. Uno es el abierto y el otro es el cerrado.


ABIERTO (Direccionamiento cerrado)

Basicamente tengo un vector de punteros del tamanio del hash se almacenan los elementos en un tipo de dato (comunmente una 
lista) en el cual se van insertando los elementos. Algo asi como:

Tamaño hash = 4

CLAVES				POSICION				VALOR  				TABLA
				(valor devuelto por
				la funcion hash)

																 ____
UNO						2 					 918				|	 |0 -----> []->[TRES,205]
																|____|
																|	 |1 -----> []
DOS 					2 					 172				|____|
																|	 |2 -----> []->[UNO,918]->[DOS,172]
																|____|
TRES					0					 205				|	 |3 -----> []
																------


CERRADO (Direccionamiento abierto)

En un hash cerrado, todos los valores se guardan adentro de la misma tabla. Ejemplo grafico:

POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								
												|---|
0				 		CERO					|281|
												|---|
1		   		 		DOS     				|918|			 
												|---|
2		   				---						|   |
												|---|
3				 		UNO					    |172|	
												|---|
4						---						|   |
												|---|
_______________________________________________________________________________________________________________________________
IMPLEMENTACION PARTICULAR

Para el tipo de dato hash, decidi que debia tener:

1. UNA TABLA: Esta tabla va a ser un vector con punteros a pares. Va a ser la tabla en si, lo mas importante del hash.

2. UN DESTRUCTOR: Porque me lo exigia el contrato, sirve para saber si liberar los elementos.

3. UNA CAPACIDAD MAXIMA: Sirve para saber cuantos elementos va a tener la tabla y para el factor de balanceo.

4. UN ESPACIOS OCUPADOS: Sirve para saber cuantos elementos ya ocupe de la tabla y para el factor de balanceo.

Para el tipo de dato par, decidi que debia tener una clave, un elemento y un fue_ocupada, que funciona como flag para
saber si un espacio estuvo ocupado a la hora de obtener un elemento.

La resolucion de colisiones esta solucionada de manera que si trato de insertar una clave que ya tengo, el nuevo par clave
elemento, se reemplaza por la clave y el elemento antiguos.

Tambien hice que si la mitad de la tabla se llena, rehashee y el tamanio se duplique.

Para implementar la funcion de hash, hice una funcione que buscara la longitud del vector y le aplicara la siguiente formula:

hash = longitud_string * str[longitud_string-1] + 31*str[0] + 7*str[longitud_string/2] - 1;

Esta formula, lo que hace es ir fijandose el primer caracter, el ultimo y el de enmedio (en forma ASCII) y multiplicarlos por
ciertos numeros (31 y 7 son primos e impares) tal que de un resultado que sea dificil que se repita en diferentes strings, a
modo de evitar colisiones.

Tambien implemente una funcion hash, que cuando tenia problemas me ayudo a debuggear el codigo.

INSERTAR

Para el insertar, cree una funcion auxiliar tabla_insertar que lo que hace es agarrar y fijarse que devuelve la funcion hash
cuando le pasamos la clave a insertar y se fija cual es el primer proximo espacio libre en la tabla, y ahi lo inserta el 
par creado, que lo crea el insertar con la clave y el elemento que le pasamos, y el flag fue_ocupado igual a true. Estoy
seguro que va a haber un espacio libre porque siempre que la mitad de los espacios ocupados, el tamaño de la tabla se va a
duplicar, con un rehash. Cree la funcion auxiliar porque me sirvio para usarla en el rehash.

Cuando explico las coliciones, di un ejemplo grafico de que pasaria en caso de una colision en mi implementacion.

Tambien, una vez termino el insertar, me fijo si tengo que hacer un rehash, y si es asi, lo hago.

DESTRUIR

Para el destruir, cree una funcion auxiliar tabla destruir, que lo que hace es liberar una tabla, que es un puntero a par_t**.
Basicamente va recorriendo la tabla y se fija si en esa posicion hay un puntero a par, y si lo hay, lo libera.
Cree la funcion auxiliar porque me sirvio para usarla en el rehash. Ejemplo:

Tengo la siguiente tabla:

POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								
												|---|
0				 		CERO					|281|
												|---|
1		   		 		DOS     				|918|			 
												|---|
2		   				---						|   |
												|---|
3				 		UNO					    |172|	
												|---|
4						---						|   |
												|---|

Empiezo a liberar:

POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								
												|---|
0				 		CERO					|281|			---> LIBERO SI HAY UN PAR ACA (HAY)
												|---|
1		   		 		DOS     				|918|			 
												|---|
2		   				---						|   |
												|---|
3				 		UNO					    |172|	
												|---|
4						---						|   |
												|---|

POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								
												|---|
0				 		---						|	|
												|---|
1		   		 		DOS     				|918|			---> LIBERO SI HAY UN PAR ACA (HAY)	 
												|---|
2		   				---						|   |
												|---|
3				 		UNO					    |172|	
												|---|
4						---						|   |
												|---|


POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								
												|---|
0				 		---						|	|
												|---|
1		   		 		---     				|	|						 
												|---|
2		   				---						|   |			---> LIBERO SI HAY UN PAR ACA (NO HAY)
												|---|
3				 		UNO					    |172|	
												|---|
4						---						|   |
												|---|


POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								
												|---|
0				 		---						|	|
												|---|
1		   		 		---     				|	|						 
												|---|
2		   				---						|   |			
												|---|
3				 		UNO					    |172|			---> LIBERO SI HAY UN PAR ACA (HAY)
												|---|
4						---						|   |
												|---|


POSICION				CLAVES				TABLA DE HASH
(valor que devuelve
la funvion de hash)								
												|---|
0				 		---						|	|
												|---|
1		   		 		---     				|	|						 
												|---|
2		   				---						|   |			
												|---|
3				 		---					    |	|			
												|---|
4						---						|   |
												|---|			---> LIBERO SI HAY UN PAR ACA (NO HAY)


Cuando la tabla ya esta completamente liberada, con los pares liberados, libero el hash.

REHASH

Para el rehash, lo que hice fue agarrar y crear una nueva tabla con el doble de la capacidad actual, e ir volviendo a
insertar los pares de la tabla vieja a la tabla nueva, y cuando termino, libero la tabla vieja y meto la tabla nueva en el
hash. Es importante aclarar que se reinician las flags fue_ocupado de los pares.

QUITAR

Para el quitar, implemente una funcion que primero pide a la funcion de hash que le devuelva el valor de la clave, se posiciona
en ese par de la tabla, y va iterando para adelanta hasta que:

1. Encuentra la clave, en cuyo caso la borra.
2. Encuentra un NULL, lo que significa que la clave a borrar no esta en el hash, y devuelve error.

OBTENER

Para el obtener, la funcion lo que hace es pedirle el valor de la clave a la funcion hash, y lo que hace es se va a esa posicion
y se fija si ahi esta la clave que busca, si es, devuelve el elemento que tiene la clave.
En cambio, si en la posicion que le devolvio la funcion de hash, no hay ningun par, ni hubo ninguno, devuelve NULL.
Sino si ese lugar tiene un par o si tuvo en algun momento (lo chequeo con el flag), ahi lo que hago es me vuelvo a fijar con el
proximo par.

MOSTRAR

Para solucionar algunos bugs que se me complicaron durante la implementacion, implemente una funcion de mostrar el hash, que
basicamente lo que hace es mostrar el hash. La dejo por si es de alguna utilidad.
